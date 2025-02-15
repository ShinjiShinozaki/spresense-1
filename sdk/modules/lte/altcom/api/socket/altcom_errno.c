/****************************************************************************
 * modules/lte/altcom/api/socket/altcom_errno.c
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

#include "dbg_if.h"
#include "altcom_errno.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

static int32_t g_altcom_errno;

/****************************************************************************
 * Inline functions
 ****************************************************************************/

static inline void altcom_errno_chkno(int32_t err_no)
{
  if (ALTCOM_ERRNO_MIN > err_no || ALTCOM_ERRNO_MAX < err_no)
    {
      DBGIF_ASSERT(NULL, "seterrno invalid param. \n");
    }
}
/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: altcom_errno
 *
 * Description:
 *   Get errno for socket APIs.
 *
 * Input parameters:
 *   None
 *
 *  Return:
 *   errno
 *
 ****************************************************************************/

int32_t altcom_errno(void)
{
  return g_altcom_errno;
}

/****************************************************************************
 * Name: altcom_seterrno
 *
 * Description:
 *   Set errno for socket APIs.
 *
 * Input parameters:
 *   errno
 *
 *  Return:
 *   None
 *
 ****************************************************************************/

void altcom_seterrno(int32_t err_no)
{
  altcom_errno_chkno(err_no);
  g_altcom_errno = err_no;
  return;
}

