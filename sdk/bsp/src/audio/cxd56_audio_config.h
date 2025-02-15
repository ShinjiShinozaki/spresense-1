/****************************************************************************
 * bsp/src/audio/cxd56_audio_config.h
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

#ifndef __BSP_SRC_AUDIO_CXD56_AUDIO_CONFIG_H
#define __BSP_SRC_AUDIO_CXD56_AUDIO_CONFIG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <sdk/config.h>
#include <arch/chip/cxd56_audio.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

enum cxd56_audio_cfg_mic_mode_e
{
  CXD56_AUDIO_CFG_MIC_MODE_64FS = 0,
  CXD56_AUDIO_CFG_MIC_MODE_128FS
};

enum cxd56_audio_cfg_mic_dev_e
{
  CXD56_AUDIO_CFG_MIC_DEV_NONE = 0,
  CXD56_AUDIO_CFG_MIC_DEV_ANALOG,
  CXD56_AUDIO_CFG_MIC_DEV_DIGITAL,
  CXD56_AUDIO_CFG_MIC_DEV_ANADIG
};

enum cxd56_audio_cfg_mic_bias_e
{
  CXD56_AUDIO_CFG_MIC_BIAS_20V = 0,
  CXD56_AUDIO_CFG_MIC_BIAS_28V
};

enum cxd56_audio_cfg_xtal_e
{
  CXD56_AUDIO_CFG_XTAL_24_576MHZ = 0,
  CXD56_AUDIO_CFG_XTAL_49_152MHZ
};

enum cxd56_audio_cfg_ds_e
{
  CXD56_AUDIO_CFG_DS_WEAKEST = 0,
  CXD56_AUDIO_CFG_DS_WEAKER,
  CXD56_AUDIO_CFG_DS_STRONGER,
  CXD56_AUDIO_CFG_DS_STRONGEST
};

enum cxd56_audio_cfg_i2s_mode_e
{
  CXD56_AUDIO_CFG_I2S_MODE_MASTER = 0,
  CXD56_AUDIO_CFG_I2S_MODE_SLAVE
};

enum cxd56_audio_cfg_i2s_format_e
{
  CXD56_AUDIO_CFG_I2S_FORMAT_NORMAL = 0,
  CXD56_AUDIO_CFG_I2S_FORMAT_LEFT
};

enum cxd56_audio_cfg_i2s_bypass_e
{
  CXD56_AUDIO_CFG_I2S_BYPASS_DISABLE = 0,
  CXD56_AUDIO_CFG_I2S_BYPASS_ENABLE
};

enum cxd56_audio_cfg_lowemi_e
{
  CXD56_AUDIO_CFG_LOEMI_2MA = 0,
  CXD56_AUDIO_CFG_LOEMI_4MA
};

enum cxd56_audio_cfg_cic_in_sel_e
{
  CXD56_AUDIO_CFG_CIC_IN_SEL_NONE = 0,
  CXD56_AUDIO_CFG_CIC_IN_SEL_CXD,
  CXD56_AUDIO_CFG_CIC_IN_SEL_DMICIF
};

enum cxd56_audio_cfg_alc_spc_sel_e
{
  CXD56_AUDIO_CFG_ALCSPC_NONE = 0,
  CXD56_AUDIO_CFG_ALCSPC_ALC,
  CXD56_AUDIO_CFG_ALCSPC_SPC
};

#define CXD56_AUDIO_CFG_SPC_LIMIT_DEFAULT  0
#define CXD56_AUDIO_CFG_ALC_TARGET_DEFAULT 0
#define CXD56_AUDIO_CFG_ALC_KNEE_DEFAULT   0

enum cxd56_audio_cfg_dma_formatl_e
{
  CXD56_AUDIO_CFG_DMA_FORMAT_LR = 0,
  CXD56_AUDIO_CFG_DMA_FORMAT_RL
};

enum cxd56_audio_cfg_hpadc_mic_bias_e
{
  CXD56_AUDIO_CFG_HPADC_MIC_BIAS_OFF = 0,
  CXD56_AUDIO_CFG_HPADC_MIC_BIAS_ON
};

enum cxd56_audio_cfg_sp_spliton_e
{
  CXD56_AUDIO_CFG_SP_SPLITON_LONGEST = 0,
  CXD56_AUDIO_CFG_SP_SPLITON_LONG,
  CXD56_AUDIO_CFG_SP_SPLITON_SHORT,
  CXD56_AUDIO_CFG_SP_SPLITON_SHORTEST
};

/* Mic bias voltage select */

#if defined(CONFIG_CXD56_AUDIO_MICBIAS_20V)
#  define CXD56_AUDIO_CFG_MIC_BIAS   CXD56_AUDIO_CFG_MIC_BIAS_20V
#else
#  define CXD56_AUDIO_CFG_MIC_BIAS   CXD56_AUDIO_CFG_MIC_BIAS_28V
#endif

/* Master clock select */

#if defined(CONFIG_CXD56_AUDIO_XTAL_SEL_49_152MHZ)
#  define CXD56_AUDIO_CFG_MCLK   CXD56_AUDIO_CFG_XTAL_49_152MHZ
#else
#  define CXD56_AUDIO_CFG_MCLK   CXD56_AUDIO_CFG_XTAL_24_576MHZ
#endif

/* Mic select */

#define CXD56_AUDIO_CFG_MIC   CONFIG_CXD56_AUDIO_MIC_CHANNEL_SEL

/* Drive strength of global pin output-A */

#if defined(CONFIG_CXD56_AUDIO_GPO_A_WEAKEST)
#  define CXD56_AUDIO_CFG_GPO_A_DS    CXD56_AUDIO_CFG_DS_WEAKEST
#elif defined(CONFIG_CXD56_AUDIO_GPO_A_WEAKER)
#  define CXD56_AUDIO_CFG_GPO_A_DS    CXD56_AUDIO_CFG_DS_WEAKER
#elif defined(CONFIG_CXD56_AUDIO_GPO_A_STRONGER)
#  define CXD56_AUDIO_CFG_GPO_A_DS    CXD56_AUDIO_CFG_DS_STRONGER
#else
#  define CXD56_AUDIO_CFG_GPO_A_DS    CXD56_AUDIO_CFG_DS_STRONGEST
#endif

/* Drive strength of D/A converted data */

#if defined(CONFIG_CXD56_AUDIO_DA_DATA_WEAKEST)
#  define CXD56_AUDIO_CFG_DA_DS    CXD56_AUDIO_CFG_DS_WEAKEST
#elif defined(CONFIG_CXD56_AUDIO_DA_DATA_WEAKER)
#  define CXD56_AUDIO_CFG_DS_DS    CXD56_AUDIO_CFG_DS_WEAKER
#elif defined(CONFIG_CXD56_AUDIO_DA_DATA_STRONGER)
#  define CXD56_AUDIO_CFG_DA_DS    CXD56_AUDIO_CFG_DS_STRONGER
#else
#  define CXD56_AUDIO_CFG_DA_DS    CXD56_AUDIO_CFG_DS_STRONGEST
#endif

/* Drive strength of digital mic clock */

#if defined(CONFIG_CXD56_AUDIO_CLKOUT_DMIC_WEAKEST)
#  define CXD56_AUDIO_CFG_DMIC_CLK_DS    CXD56_AUDIO_CFG_DS_WEAKEST
#elif defined(CONFIG_CXD56_AUDIO_CLKOUT_DMIC_WEAKER)
#  define CXD56_AUDIO_CFG_DMIC_CLK_DS    CXD56_AUDIO_CFG_DS_WEAKER
#elif defined(CONFIG_CXD56_AUDIO_CLKOUT_DMIC_STRONGER)
#  define CXD56_AUDIO_CFG_DMIC_CLK_DS    CXD56_AUDIO_CFG_DS_STRONGER
#else
#  define CXD56_AUDIO_CFG_DMIC_CLK_DS    CXD56_AUDIO_CFG_DS_STRONGEST
#endif

/* Drive strength of master clock */

#if defined(CONFIG_CXD56_AUDIO_MCLKOUT_WEAKEST)
#  define CXD56_AUDIO_CFG_MCLKOUT_DS    CXD56_AUDIO_CFG_DS_WEAKEST
#elif defined(CONFIG_CXD56_AUDIO_MCLKOUT_WEAKER)
#  define CXD56_AUDIO_CFG_MCLKOUT_DS    CXD56_AUDIO_CFG_DS_WEAKER
#elif defined(CONFIG_CXD56_AUDIO_MCLKOUT_STRONGER)
#  define CXD56_AUDIO_CFG_MCLKOUT_DS    CXD56_AUDIO_CFG_DS_STRONGER
#else
#  define CXD56_AUDIO_CFG_MCLKOUT_DS    CXD56_AUDIO_CFG_DS_STRONGEST
#endif

/* I2S mode of I2S1 */

#if defined(CONFIG_CXD56_AUDIO_I2S_DEVICE_1_MASTER)
#  define CXD56_AUDIO_CFG_I2S1_MODE    CXD56_AUDIO_CFG_I2S_MODE_MASTER
#else
#  define CXD56_AUDIO_CFG_I2S1_MODE    CXD56_AUDIO_CFG_I2S_MODE_SLAVE
#endif

/* I2S format of I2S1 */

#if defined(CONFIG_CXD56_AUDIO_I2S_FORMAT_1_LEFT)
#  define CXD56_AUDIO_CFG_I2S1_FORMAT  CXD56_AUDIO_CFG_I2S_FORMAT_LEFT
#else
#  define CXD56_AUDIO_CFG_I2S1_FORMAT  CXD56_AUDIO_CFG_I2S_FORMAT_NORMAL
#endif

/* I2S bypass mode of I2S1 */

#if defined(CONFIG_CXD56_AUDIO_I2S_BYPASS_MODE_1_ENABLE)
#  define CXD56_AUDIO_CFG_I2S1_BYPASS  CXD56_AUDIO_CFG_I2S_BYPASS_ENABLE
#else
#  define CXD56_AUDIO_CFG_I2S1_BYPASS  CXD56_AUDIO_CFG_I2S_BYPASS_DISABLE
#endif

/* I2S data rate of I2S1 */

#if defined(CONFIG_CXD56_I2S0)
#  define CXD56_AUDIO_CFG_I2S1_DATA_RATE   CONFIG_CXD56_AUDIO_I2S_RATE_1
#else
#  define CXD56_AUDIO_CFG_I2S1_DATA_RATE   0
#endif

/* I2S mode of I2S2 */

#if defined(CONFIG_CXD56_AUDIO_I2S_DEVICE_2_MASTER)
#  define CXD56_AUDIO_CFG_I2S2_MODE    CXD56_AUDIO_CFG_I2S_MODE_MASTER
#else
#  define CXD56_AUDIO_CFG_I2S2_MODE    CXD56_AUDIO_CFG_I2S_MODE_SLAVE
#endif

/* I2S format of I2S2 */

#if defined(CONFIG_CXD56_AUDIO_I2S_FORMAT_2_LEFT)
#  define CXD56_AUDIO_CFG_I2S2_FORMAT  CXD56_AUDIO_CFG_I2S_FORMAT_LEFT
#else
#  define CXD56_AUDIO_CFG_I2S2_FORMAT  CXD56_AUDIO_CFG_I2S_FORMAT_NORMAL
#endif

/* I2S bypass mode of I2S2 */

#if defined(CONFIG_CXD56_AUDIO_I2S_BYPASS_MODE_2_ENABLE)
#  define CXD56_AUDIO_CFG_I2S2_BYPASS  CXD56_AUDIO_CFG_I2S_BYPASS_ENABLE
#else
#  define CXD56_AUDIO_CFG_I2S2_BYPASS  CXD56_AUDIO_CFG_I2S_BYPASS_DISABLE
#endif

/* I2S data rate of I2S2 */
#if defined(CONFIG_CXD56_I2S1)
#  define CXD56_AUDIO_CFG_I2S2_DATA_RATE   CONFIG_CXD56_AUDIO_I2S_RATE_2
#else
#  define CXD56_AUDIO_CFG_I2S2_DATA_RATE   0
#endif

/* Drive strength of PDM signals */

#if defined(CONFIG_CXD56_AUDIO_PDM_LOWEMI_2MA)
#  define CXD56_AUDIO_CFG_PDM_DS CXD56_AUDIO_CFG_LOEMI_2MA
#else
#  define CXD56_AUDIO_CFG_PDM_DS CXD56_AUDIO_CFG_LOEMI_4MA
#endif

/* Drive strength of I2S signals */

#if defined(CONFIG_CXD56_AUDIO_I2S_LOWEMI_2MA)
#  define CXD56_AUDIO_CFG_I2S_DS CXD56_AUDIO_CFG_LOEMI_2MA
#else
#  define CXD56_AUDIO_CFG_I2S_DS CXD56_AUDIO_CFG_LOEMI_4MA
#endif

/* CIC filter input path */

#if defined(CONFIG_CXD56_AUDIO_CIC_IN_SEL_CXD)
#  define CXD56_AUDIO_CFG_CIC_IN  CXD56_AUDIO_CFG_CIC_IN_SEL_CXD
#elif defined (CONFIG_CXD56_AUDIO_CIC_IN_SEL_DMIC)
#  define CXD56_AUDIO_CFG_CIC_IN  CXD56_AUDIO_CFG_CIC_IN_SEL_DMICIF
#else
#  define CXD56_AUDIO_CFG_CIC_IN  CXD56_AUDIO_CFG_CIC_IN_SEL_NONE
#endif

/* Wait time of mic boot */

#define CXD56_AUDIO_MIC_BOOT_WAIT CONFIG_CXD56_AUDIO_MIC_BOOT_WAIT

/* ALC and SPC filter select */

#if defined(CONFIG_CXD56_AUDIO_ALC_SPC_SEL_OFF)
#  define CXD56_AUDIO_CFG_ALCSPC  CXD56_AUDIO_CFG_ALCSPC_NONE
#elif defined (CONFIG_CXD56_AUDIO_ALC_SPC_SEL_ALC)
#  define CXD56_AUDIO_CFG_ALCSPC  CXD56_AUDIO_CFG_ALCSPC_ALC
#else
#  define CXD56_AUDIO_CFG_ALCSPC  CXD56_AUDIO_CFG_ALCSPC_SPC
#endif

/* SPC limit level */

#if defined(CONFIG_CXD56_AUDIO_ALC_SPC_SEL_SPC)
#  define CXD56_AUDIO_CFG_SPC_LIMIT  CONFIG_CXD56_AUDIO_SPC_LIMIT
#else
#  define CXD56_AUDIO_CFG_SPC_LIMIT  CXD56_AUDIO_CFG_SPC_LIMIT_DEFAULT
#endif

/* ALC target level */

#if defined(CONFIG_CXD56_AUDIO_ALC_SPC_SEL_ALC)
#  define CXD56_AUDIO_CFG_ALC_TARGET   CONFIG_CXD56_AUDIO_ALC_TARGET
#else
#  define CXD56_AUDIO_CFG_ALC_TARGET   CXD56_AUDIO_CFG_ALC_TARGET_DEFAULT
#endif

/* ALC knee point */

#if defined(CONFIG_CXD56_AUDIO_ALC_SPC_SEL_ALC)
#  define CXD56_AUDIO_CFG_ALC_KNEE  CONFIG_CXD56_AUDIO_ALC_KNEE
#else
#  define CXD56_AUDIO_CFG_ALC_KNEE  CXD56_AUDIO_CFG_ALC_KNEE_DEFAULT
#endif

/* DMA format */

#if defined(CONFIG_CXD56_AUDIO_DMA_DATA_FORMAT_LR)
#  define CXD56_AUDIO_CFG_DMA_FORMAT  CXD56_AUDIO_CFG_DMA_FORMAT_LR
#else
#  define CXD56_AUDIO_CFG_DMA_FORMAT  CXD56_AUDIO_CFG_DMA_FORMAT_RL
#endif

/* Mic bias for HPADC */

#if defined(CONFIG_CXD56_AUDIO_HPADC_MIC_BIAS_ON)
#  define CXD56_AUDIO_CFG_HPADC_MIC_BIAS  CXD56_AUDIO_CFG_HPADC_MIC_BIAS_ON
#else
#  define CXD56_AUDIO_CFG_HPADC_MIC_BIAS  CXD56_AUDIO_CFG_HPADC_MIC_BIAS_OFF
#endif

/* Speaker time split on drive */

#if defined(CONFIG_CXD56_AUDIO_SP_SPLIT_LONGEST)
#  define CXD56_AUDIO_CFG_SP_SPLIT_ON    CXD56_AUDIO_CFG_SP_SPLITON_LONGEST
#elif defined(CONFIG_CXD56_AUDIO_SP_SPLIT_LONG)
#  define CXD56_AUDIO_CFG_SP_SPLIT_ON    CXD56_AUDIO_CFG_SP_SPLITON_LONG
#elif defined(CONFIG_CXD56_AUDIO_SP_SPLIT_SHORT)
#  define CXD56_AUDIO_CFG_SP_SPLIT_ON    CXD56_AUDIO_CFG_SP_SPLITON_SHORT
#else
#  define CXD56_AUDIO_CFG_SP_SPLIT_ON    CXD56_AUDIO_CFG_SP_SPLITON_SHORTEST
#endif

/* Speaker drive mode */

#if defined(CONFIG_CXD56_AUDIO_SP_DRV_LINEOUT)
#  define CXD56_AUDIO_CFG_SP_DRIVER   CXD56_AUDIO_SP_DRV_LINEOUT
#elif defined(CONFIG_CXD56_AUDIO_SP_DRV_1DRIVERT)
#  define CXD56_AUDIO_CFG_SP_DRIVER   CXD56_AUDIO_SP_DRV_1DRIVER
#elif defined(CONFIG_CXD56_AUDIO_SP_DRV_2DRIVERT)
#  define CXD56_AUDIO_CFG_SP_DRIVER   CXD56_AUDIO_SP_DRV_2DRIVER
#else
#  define CXD56_AUDIO_CFG_SP_DRIVER   CXD56_AUDIO_SP_DRV_4DRIVER
#endif


/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void cxd56_audio_config_init(void);
uint8_t cxd56_audio_config_get_micmode(void);
uint8_t cxd56_audio_config_get_micdev(void);
uint8_t cxd56_audio_config_get_micnum(void);
void cxd56_audio_config_set_spdriver(cxd56_audio_sp_drv_t sp_driver);
cxd56_audio_sp_drv_t cxd56_audio_config_get_spdriver(void);
void cxd56_audio_config_set_clkmode(cxd56_audio_clkmode_t mode);
cxd56_audio_clkmode_t cxd56_audio_config_get_clkmode(void);

#endif /* __BSP_SRC_AUDIO_CXD56_AUDIO_CONFIG_H */
