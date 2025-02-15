/****************************************************************************
 * modules/lte/altcom/api/lte/lte_power.c
 *
 *   Copyright 2018 Sony Semiconductor Solutions Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Sony Semiconductor Solutions Corporation nor
 *    the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <sdk/config.h>

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <nuttx/modem/altmdm.h>

#include "lte/lte_api.h"
#include "wrkrid.h"
#include "apicmd.h"
#include "apiutil.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef CONFIG_MODEM_DEVICE_PATH
#  define DEV_PATH CONFIG_MODEM_DEVICE_PATH
#else
#  warning "CONFIG_MODEM_DEVICE_PATH not defined"
#  define DEV_PATH "/dev/altmdm"
#endif

#define POWERON_DATA_LEN     (0)

/****************************************************************************
 * Private Data
 ****************************************************************************/

extern power_control_cb_t g_lte_power_callback;

/****************************************************************************
 * Public Data
 ****************************************************************************/

extern void lte_callback_init(void);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: power_callback_job
 *
 * Description:
 *   This function is an API callback for power.
 *
 * Input Parameters:
 *  arg    Pointer to input argment.
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

static void power_callback_job(FAR void *arg)
{
  int32_t            ret;
  power_control_cb_t callback = NULL;

  ALTCOM_GET_AND_CLR_CALLBACK(ret, g_lte_power_callback, callback);

  if ((0 == ret) && (callback))
    {
      callback(LTE_RESULT_OK);
      lte_callback_init();
    }
  else
    {
      DBGIF_LOG_ERROR("Unexpected!! callback is NULL.\n");
    }
}

/****************************************************************************
 * Name: modem_powerctrl
 *
 * Description:
 *   Power on or off the modem.
 *
 * Input Parameters:
 *  on  "power on" or "power off".
 *
 * Returned Value:
 *   On success, 0 is returned.
 *   On failure, negative value is returned.
 *
 ****************************************************************************/

int32_t modem_powerctrl(bool on)
{
  int32_t  ret;
  int      fd;
  int      l_errno;
  int      req;

  /* Open the device */

  fd = open(DEV_PATH, O_WRONLY);
  if (0 > fd)
    {
      DBGIF_LOG2_ERROR("Device %s open failure. %d\n", DEV_PATH, fd);
      ret = fd;
    }
  else
    {
      if (on)
        {
          req = MODEM_IOC_POWERON;
        }
      else
        {
          req = MODEM_IOC_POWEROFF;
        }

      /* Power on the modem */

      ret = ioctl(fd, req, 0);
      if (0 > ret)
        {
          /* Store errno */

          l_errno = errno;
          ret = -l_errno;

          DBGIF_LOG2_ERROR("Failed to ioctl(0x%08x). %d\n", req, l_errno);
          
        }

      close(fd);
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lte_power_control
 *
 * Description:
 *   Control power on/off of modem.
 *
 * Input Parameters:
 *   on       "power on" or "power off".
 *   callback Callback function to notify that power on/off has been
 *            completed.
 *
 * Returned Value:
 *   On success, 0 is returned.
 *   On failure, negative value is returned.
 *
 ****************************************************************************/

int32_t lte_power_control(bool on, power_control_cb_t callback)
{
  int32_t     ret;
  FAR uint8_t *cmdbuff;

  /* Return error if callback is NULL */

  if (!callback)
    {
      DBGIF_LOG_ERROR("Input argument is NULL.\n");
      return -EINVAL;
    }

  /* Check if the library is initialized */

  if (!altcom_isinit())
    {
      DBGIF_LOG_ERROR("Not intialized\n");
      ret = -EPERM;
    }
  else
    {
      /* Register API callback */

      ALTCOM_REG_CALLBACK(ret, g_lte_power_callback, callback);
      if (0 > ret)
        {
          DBGIF_LOG_ERROR("Currently API is busy.\n");
        }
    }

  /* Accept the API */

  if (0 == ret)
    {
      /* Power on or off the modem */

      ret = modem_powerctrl(on);

      /* If fail, there is no opportunity to execute the callback,
       * so clear it here. */

      if (0 > ret)
        {
          /* Clear registered callback */

          ALTCOM_CLR_CALLBACK(g_lte_power_callback);
          return ret;
        }

      if (LTE_POWERON == on)
        {
          /* Allocate API command buffer to send */

          cmdbuff = apicmdgw_cmd_allocbuff(APICMDID_POWER_ON,
            POWERON_DATA_LEN);
          if (!cmdbuff)
            {
              DBGIF_LOG_ERROR("Failed to allocate command buffer.\n");
              ret = -ENOMEM;
            }
          else
            {
              /* Send API command to modem */

              ret = altcom_send_and_free(cmdbuff);
            }

          /* If fail, there is no opportunity to execute the callback,
           * so clear it here. */

          if (0 > ret)
            {
              /* Clear registered callback */

              ALTCOM_CLR_CALLBACK(g_lte_power_callback);

              (void)modem_powerctrl(false);
            }
          else
            {
              ret = 0;
            }
        }
      else
        {
          /* Call the API callback function in the context of worker thread */

          ret = altcom_runjob(WRKRID_API_CALLBACK_THREAD,
                               power_callback_job, NULL);
          DBGIF_ASSERT(0 == ret, "Failed to job to worker\n");
        }
    }

  return ret;
}
