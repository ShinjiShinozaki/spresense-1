/****************************************************************************
 * modules/lte/altcom/api/lte/lte_attach_net.c
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

#include <stdint.h>
#include <errno.h>

#include "lte/lte_api.h"
#include "apiutil.h"
#include "apicmd_atchnet.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define ATTACH_NET_DATA_LEN (0)

/****************************************************************************
 * Public Data
 ****************************************************************************/

extern attach_net_cb_t g_attach_net_callback;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lte_attach_network
 *
 * Description:
 *   Attach to the LTE network.
 *
 * Input Parameters:
 *   callback Callback function to notify that attach completed.
 *
 * Returned Value:
 *   On success, 0 is returned.
 *   On failure, negative value is returned.
 *
 ****************************************************************************/

int32_t lte_attach_network(attach_net_cb_t callback)
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

      ALTCOM_REG_CALLBACK(ret, g_attach_net_callback, callback);
      if (0 > ret)
        {
          DBGIF_LOG_ERROR("Currently API is busy.\n");
        }
    }

  /* Accept the API */

  if (0 == ret)
    {
      /* Allocate API command buffer to send */

      cmdbuff = (FAR uint8_t *)apicmdgw_cmd_allocbuff(APICMDID_ATTACH_NET,
        ATTACH_NET_DATA_LEN);
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

          ALTCOM_CLR_CALLBACK(g_attach_net_callback);
        }
      else
        {
          ret = 0;
        }
    }

  return ret;
}
