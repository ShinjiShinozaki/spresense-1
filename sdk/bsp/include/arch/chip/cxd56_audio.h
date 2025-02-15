/****************************************************************************
 * bsp/include/arch/chip/cxd56_audio.h
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
/**
 * @defgroup audioutils Audio Utility
 * @{
 */

#ifndef __BSP_INCLUDE_ARCH_CHIP_CXD56_AUDIO_H
#define __BSP_INCLUDE_ARCH_CHIP_CXD56_AUDIO_H

/* API Documents creater with Doxgen */

/**
 * @defgroup cxd56_audio_api Audio Driver API
 * @{
 *
 * @file       cxd56_audio.h
 * @brief      CXD5602 Audio Driver API
 * @author     CXD5602 Audio SW Team
 */

/****************************************************************************
 * Included Files
 ***************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ***************************************************************************/

/** Mic channel max. */

#define CXD56_AUDIO_MIC_CH_MAX      8

/** DNC binary size. */

#define CXD56_AUDIO_DNC_FW_SIZE    512
#define CXD56_AUDIO_DNC_CFG_SIZE   128

/** DEQ band number. */

#define CXD56_AUDIO_DEQ_BAND_NUM     6

/****************************************************************************
 * Public Types
 ****************************************************************************/

/** cxd56_audio common return code. */

#define CXD56_AUDIO_ECODE uint16_t

#define CXD56_AUDIO_ECODE_OK          0x0000
#define CXD56_AUDIO_ECODE_POW         0x1000
#define CXD56_AUDIO_ECODE_FIL         0x2000
#define CXD56_AUDIO_ECODE_MIC         0x3000
#define CXD56_AUDIO_ECODE_VOL         0x4000
#define CXD56_AUDIO_ECODE_DIG         0x5000
#define CXD56_AUDIO_ECODE_BEP         0x6000
#define CXD56_AUDIO_ECODE_INT         0x7000
#define CXD56_AUDIO_ECODE_DMA         0x8000
#define CXD56_AUDIO_ECODE_ANA         0x9000
#define CXD56_AUDIO_ECODE_REG         0xA000
#define CXD56_AUDIO_ECODE_CFG         0xB000

/* Error code of power */

#define CXD56_AUDIO_ECODE_POW_STATE     (CXD56_AUDIO_ECODE_POW | 0x01)

/* Error code of filter */

#define CXD56_AUDIO_ECODE_FIL_DNC_BIN     (CXD56_AUDIO_ECODE_FIL | 0x01)

/* Error code of mic */

#define CXD56_AUDIO_ECODE_MIC_NO_ANA      (CXD56_AUDIO_ECODE_MIC | 0x01)
#define CXD56_AUDIO_ECODE_MIC_ARG_NULL    (CXD56_AUDIO_ECODE_MIC | 0x02)

/* Error code of volume */

#define CXD56_AUDIO_ECODE_VOL_ID  (CXD56_AUDIO_ECODE_VOL | 0x01)
#define CXD56_AUDIO_ECODE_VOL_MAX (CXD56_AUDIO_ECODE_VOL | 0x02)
#define CXD56_AUDIO_ECODE_VOL_MIN (CXD56_AUDIO_ECODE_VOL | 0x03)

/* Error code of digital */

/* Error code of beep */

#define CXD56_AUDIO_ECODE_BEP_FREQ_MAX (CXD56_AUDIO_ECODE_BEP | 0x01)
#define CXD56_AUDIO_ECODE_BEP_FREQ_MIN (CXD56_AUDIO_ECODE_BEP | 0x02)
#define CXD56_AUDIO_ECODE_BEP_VOL_MAX  (CXD56_AUDIO_ECODE_BEP | 0x03)
#define CXD56_AUDIO_ECODE_BEP_VOL_MIN  (CXD56_AUDIO_ECODE_BEP | 0x04)

/* Error code of interrupt */

/* Error code of dma */

#define CXD56_AUDIO_ECODE_DMA_ARG_NULL     (CXD56_AUDIO_ECODE_DMA | 0x01)
#define CXD56_AUDIO_ECODE_DMA_PATH_INV     (CXD56_AUDIO_ECODE_DMA | 0x02)
#define CXD56_AUDIO_ECODE_DMA_PATH_COMB    (CXD56_AUDIO_ECODE_DMA | 0x03)
#define CXD56_AUDIO_ECODE_DMA_PATH_DUP     (CXD56_AUDIO_ECODE_DMA | 0x04)
#define CXD56_AUDIO_ECODE_DMA_PATH_MAX     (CXD56_AUDIO_ECODE_DMA | 0x05)
#define CXD56_AUDIO_ECODE_DMA_HANDLE_NULL  (CXD56_AUDIO_ECODE_DMA | 0x06)
#define CXD56_AUDIO_ECODE_DMA_HANDLE_INV   (CXD56_AUDIO_ECODE_DMA | 0x07)
#define CXD56_AUDIO_ECODE_DMA_CH_NO_ENABLE (CXD56_AUDIO_ECODE_DMA | 0x08)
#define CXD56_AUDIO_ECODE_DMA_CH1_4_INV    (CXD56_AUDIO_ECODE_DMA | 0x09)
#define CXD56_AUDIO_ECODE_DMA_CH5_8_INV    (CXD56_AUDIO_ECODE_DMA | 0x0a)
#define CXD56_AUDIO_ECODE_DMA_SMP_TIMEOUT  (CXD56_AUDIO_ECODE_DMA | 0x0b)
#define CXD56_AUDIO_ECODE_DMA_BUSY         (CXD56_AUDIO_ECODE_DMA | 0x0c)

#define CXD56_AUDIO_ECODE_DMA_CMPLT        (CXD56_AUDIO_ECODE_DMA | 0x11)
#define CXD56_AUDIO_ECODE_DMA_TRANS        (CXD56_AUDIO_ECODE_DMA | 0x12)
#define CXD56_AUDIO_ECODE_DMA_CMB          (CXD56_AUDIO_ECODE_DMA | 0x13)

/* Error code of analog */

#define CXD56_AUDIO_ECODE_ANA_DISABLE        (CXD56_AUDIO_ECODE_ANA | 0x01)
#define CXD56_AUDIO_ECODE_ANA_PWON           (CXD56_AUDIO_ECODE_ANA | 0x02)
#define CXD56_AUDIO_ECODE_ANA_PWOFF          (CXD56_AUDIO_ECODE_ANA | 0x03)
#define CXD56_AUDIO_ECODE_ANA_CLK_EN         (CXD56_AUDIO_ECODE_ANA | 0x04)
#define CXD56_AUDIO_ECODE_ANA_CHKID          (CXD56_AUDIO_ECODE_ANA | 0x05)
#define CXD56_AUDIO_ECODE_ANA_SERIAL         (CXD56_AUDIO_ECODE_ANA | 0x06)
#define CXD56_AUDIO_ECODE_ANA_PWON_MBIAS     (CXD56_AUDIO_ECODE_ANA | 0x07)
#define CXD56_AUDIO_ECODE_ANA_PWON_INPUT     (CXD56_AUDIO_ECODE_ANA | 0x08)
#define CXD56_AUDIO_ECODE_ANA_SET_SMASTER    (CXD56_AUDIO_ECODE_ANA | 0x09)
#define CXD56_AUDIO_ECODE_ANA_PWON_OUTPUT    (CXD56_AUDIO_ECODE_ANA | 0x0A)
#define CXD56_AUDIO_ECODE_ANA_PWOFF_INPUT    (CXD56_AUDIO_ECODE_ANA | 0x0B)
#define CXD56_AUDIO_ECODE_ANA_PWOFF_OUTPUT   (CXD56_AUDIO_ECODE_ANA | 0x0C)
#define CXD56_AUDIO_ECODE_ANA_ENABLE_OUTPUT  (CXD56_AUDIO_ECODE_ANA | 0x0D)
#define CXD56_AUDIO_ECODE_ANA_DISABLE_OUTPUT (CXD56_AUDIO_ECODE_ANA | 0x0E)
#define CXD56_AUDIO_ECODE_ANA_SET_MICGAIN    (CXD56_AUDIO_ECODE_ANA | 0x0F)
#define CXD56_AUDIO_ECODE_ANA_NOTIFY_MICBOOT (CXD56_AUDIO_ECODE_ANA | 0x10)

/* Error code of register */

#define CXD56_AUDIO_ECODE_REG_AC   (CXD56_AUDIO_ECODE_REG | 0x100)
#define CXD56_AUDIO_ECODE_REG_BCA  (CXD56_AUDIO_ECODE_REG | 0x200)

#define CXD56_AUDIO_ECODE_REG_AC_REVID     (CXD56_AUDIO_ECODE_REG_AC | 0x01)
#define CXD56_AUDIO_ECODE_REG_AC_DEVID     (CXD56_AUDIO_ECODE_REG_AC | 0x02)
#define CXD56_AUDIO_ECODE_REG_AC_MICMODE   (CXD56_AUDIO_ECODE_REG_AC | 0x03)
#define CXD56_AUDIO_ECODE_REG_AC_ALCTGT    (CXD56_AUDIO_ECODE_REG_AC | 0x04)
#define CXD56_AUDIO_ECODE_REG_AC_ALCKNEE   (CXD56_AUDIO_ECODE_REG_AC | 0x05)
#define CXD56_AUDIO_ECODE_REG_AC_SPCLIMT   (CXD56_AUDIO_ECODE_REG_AC | 0x06)
#define CXD56_AUDIO_ECODE_REG_AC_CLKMODE   (CXD56_AUDIO_ECODE_REG_AC | 0x07)
#define CXD56_AUDIO_ECODE_REG_AC_SEL_INV   (CXD56_AUDIO_ECODE_REG_AC | 0x08)
#define CXD56_AUDIO_ECODE_REG_AC_CSTE_VOL  (CXD56_AUDIO_ECODE_REG_AC | 0x09)

/* Error code of config */

#define CXD56_AUDIO_ECODE_CFG_CLK_MODE     (CXD56_AUDIO_ECODE_CFG | 0x01)

enum cxd56_audio_state_e
{
  /* Power OFF state */

  CXD56_AUDIO_POWER_STATE_OFF = 0,

  /* Power ON state */

  CXD56_AUDIO_POWER_STATE_ON
};
typedef enum cxd56_audio_state_e cxd56_audio_state_t;

enum cxd56_audio_i2s_src_byp_e
{
  /** SRC bypass disable */

  CXD56_AUDIO_I2S_BYP_DISABLE = 0,

  /** SRC bpass enable */

  CXD56_AUDIO_I2S_BYP_ENABLE,
};
typedef enum cxd56_audio_i2s_src_byp_e cxd56_audio_i2s_src_byp_t;

enum cxd56_audio_volid_e
{
  /** SDIN1_VOL */

  CXD56_AUDIO_VOLID_MIXER_IN1 = 0,

  /** SDIN2_VOL */

  CXD56_AUDIO_VOLID_MIXER_IN2,

  /** DAC_VOL */

  CXD56_AUDIO_VOLID_MIXER_OUT
};
typedef enum cxd56_audio_volid_e cxd56_audio_volid_t;


/** Select DNC type */
enum cxd56_audio_dnc_id_e
{
  /** Feed Back DNC */

  CXD56_AUDIO_DNC_ID_FB = 0,

  /** Feed Forward DNC */

  CXD56_AUDIO_DNC_ID_FF

};
typedef enum cxd56_audio_dnc_id_e cxd56_audio_dnc_id_t;

/** Select dma path in */

enum cxd56_audio_dma_path_e
{
  /** Mic to memory  */

  CXD56_AUDIO_DMA_PATH_MIC_TO_MEM = 0,

  /** I2S0 to memory  */

  CXD56_AUDIO_DMA_PATH_I2S0_TO_MEM,

  /** I2S1 to memory  */

  CXD56_AUDIO_DMA_PATH_I2S1_TO_MEM,

  /** Memory to BUS I/F1 */

  CXD56_AUDIO_DMA_PATH_MEM_TO_BUSIF1,

  /** Memory to BUS I/F2 */

  CXD56_AUDIO_DMA_PATH_MEM_TO_BUSIF2,
};
typedef enum cxd56_audio_dma_path_e cxd56_audio_dma_path_t;

/** Internal signal type */

enum cxd56_audio_signal_e
{
  /** MIC1 signal */

  CXD56_AUDIO_SIG_MIC1,

  /** MIC2 signal */

  CXD56_AUDIO_SIG_MIC2,

  /** MIC3 signal */

  CXD56_AUDIO_SIG_MIC3,

  /** MIC4 signal */

  CXD56_AUDIO_SIG_MIC4,

  /** I2S0 signal */

  CXD56_AUDIO_SIG_I2S0,

  /** I2S1 signal */

  CXD56_AUDIO_SIG_I2S1,

  /** BUS I/F1 signal */

  CXD56_AUDIO_SIG_BUSIF1,

  /** BUS I/F2 signal */

  CXD56_AUDIO_SIG_BUSIF2,

  /** MIX signal */

  CXD56_AUDIO_SIG_MIX
};
typedef enum cxd56_audio_signal_e cxd56_audio_signal_t;

/** DMAC ID to get in AS_SetAudioDataPath function */
enum cxd56_audio_dma_e
{
  /** AudioCodec input */

  CXD56_AUDIO_DMAC_MIC = 0,

  /** I2S input */

  CXD56_AUDIO_DMAC_I2S0_UP,

  /** I2S_OUT */

  CXD56_AUDIO_DMAC_I2S0_DOWN,

  /** I2S2_IN */

  CXD56_AUDIO_DMAC_I2S1_UP,

  /** I2S2_OUT */

  CXD56_AUDIO_DMAC_I2S1_DOWN
};
typedef enum cxd56_audio_dma_e cxd56_audio_dma_t;

/** Select output device ID */
enum cxd56_audio_outdev_e
{
  CXD56_AUDIO_OUTDEV_OFF = 0,
  CXD56_AUDIO_OUTDEV_SP,
  CXD56_AUDIO_OUTDEV_I2S
};
typedef enum cxd56_audio_outdev_e cxd56_audio_outdev_t;

enum cxd56_audio_clkmode_e
{
  CXD56_AUDIO_CLKMODE_NORMAL = 0,
  CXD56_AUDIO_CLKMODE_HIRES,
};
typedef enum cxd56_audio_clkmode_e cxd56_audio_clkmode_t;

enum cxd56_audio_dmafmt_e
{
  CXD56_AUDIO_DMA_FMT_LR = 0,
  CXD56_AUDIO_DMA_FMT_RL,
};
typedef enum cxd56_audio_dmafmt_e cxd56_audio_dmafmt_t;

enum cxd56_audio_samp_fmt_e
{
  CXD56_AUDIO_SAMP_FMT_24 = 0,
  CXD56_AUDIO_SAMP_FMT_16
};
typedef enum cxd56_audio_samp_fmt_e cxd56_audio_samp_fmt_t;

enum cxd56_audio_dsr_rate_e
{
  CXD56_AUDIO_DSR_1STEP = 0x0,
  CXD56_AUDIO_DSR_2STEP,
  CXD56_AUDIO_DSR_4STEP,
  CXD56_AUDIO_DSR_6STEP,
  CXD56_AUDIO_DSR_8STEP,
  CXD56_AUDIO_DSR_11STEP,
  CXD56_AUDIO_DSR_12STEP,
  CXD56_AUDIO_DSR_16STEP,
};
typedef enum cxd56_audio_dsr_rate_e cxd56_audio_dsr_rate_t;

enum cxd56_audio_dma_state_e
{
  CXD56_AUDIO_DMA_STATE_REDY = 0x0,
  CXD56_AUDIO_DMA_STATE_RUN,
};
typedef enum cxd56_audio_dma_state_e cxd56_audio_dma_state_t;

enum cxd56_audio_micdev_e
{
  CXD56_AUDIO_MIC_DEV_NONE = 0,
  CXD56_AUDIO_MIC_DEV_ANALOG,
  CXD56_AUDIO_MIC_DEV_DIGITAL,
  CXD56_AUDIO_MIC_DEV_ANADIG
};
typedef enum cxd56_audio_micdev_e cxd56_audio_micdev_t;

enum cxd56_audio_sp_drv_e
{
  CXD56_AUDIO_SP_DRV_LINEOUT = 0,
  CXD56_AUDIO_SP_DRV_1DRIVER,
  CXD56_AUDIO_SP_DRV_2DRIVER,
  CXD56_AUDIO_SP_DRV_4DRIVER
};
typedef enum cxd56_audio_sp_drv_e cxd56_audio_sp_drv_t;

struct cxd56_audio_i2s_param_s
{
  uint32_t data_rate;
  cxd56_audio_i2s_src_byp_t bypass_mode;
};
typedef struct cxd56_audio_i2s_param_s cxd56_audio_i2s_param_t;

struct cxd56_audio_mic_gain_s
{
  int32_t gain[CXD56_AUDIO_MIC_CH_MAX];
};
typedef struct cxd56_audio_mic_gain_s cxd56_audio_mic_gain_t;

struct cxd56_audio_dnc_bin_s
{
  uint32_t firm[CXD56_AUDIO_DNC_FW_SIZE];
  uint32_t config[CXD56_AUDIO_DNC_CFG_SIZE];
};
typedef struct cxd56_audio_dnc_bin_s cxd56_audio_dnc_bin_t;

struct cxd56_audio_sel_s
{
  /** Whether to select with AU_DAT_SEL1 */

  bool au_dat_sel1;

  /** Whether to select with AU_DAT_SEL2 */

  bool au_dat_sel2;

  /** Whether to select with COD_INSEL2 */

  bool cod_insel2;

  /** Whether to select with COD_INSEL3 */

  bool cod_insel3;

  /** Whether to select with SRC1IN_SEL */

  bool src1in_sel;

  /** Whether to select with SRC2IN_SEL */

  bool src2in_sel;
};
typedef struct cxd56_audio_sel_s cxd56_audio_sel_t;

struct cxd56_audio_deq_coef_func_s
{
  uint32_t b0;
  uint32_t b1;
  uint32_t b2;
  uint32_t a0;
  uint32_t a1;
};
typedef struct cxd56_audio_deq_coef_func_s cxd56_audio_deq_coef_func_t;

struct cxd56_audio_deq_coef_s
{
  cxd56_audio_deq_coef_func_t coef[CXD56_AUDIO_DEQ_BAND_NUM];
};
typedef struct cxd56_audio_deq_coef_s cxd56_audio_deq_coef_t;

struct cxd56_audio_dma_mstate_s
{
  uint8_t start;
  uint8_t err_setting;
  uint8_t buf_state;
};
typedef struct cxd56_audio_dma_mstate_s cxd56_audio_dma_mstate_t;

/** DMAC transfer callback function */

typedef void (* cxd56_audio_dma_cb_t)(cxd56_audio_dma_t handle, uint32_t code);

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Inline Functions
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief Power on Audio driver
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_poweron(void);

/**
 * @brief Power off BaseBand driver
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_poweroff(void);

/**
 * @brief Enable clear stereo
 *
 * @param[in] bool Sign inversion(false: positive, true:negative)
 * @param[in] int16_t volume, -825:-82.5dB, ... -195:-19.5dB,
 * step:5
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_cstereo(bool sign_inv, int16_t vol);

/**
 * @brief Disable clear stereo
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_cstereo(void);

/**
 * @brief Power on DNC
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_poweron_dnc(void);

/**
 * @brief Power off DNC
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_poweroff_dnc(void);

/**
 * @brief Enable DNC
 *
 * @param[in] cxd56_audio_dnc_id_t target DNC device
 * @param[in] cxd56_audio_dnc_bin_t firmware and configurator
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_dnc(cxd56_audio_dnc_id_t id,
                                     FAR cxd56_audio_dnc_bin_t *bin);

/**
 * @brief Disable DNC
 *
 * @param[in] cxd56_audio_dnc_id_t target DNC device
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_dnc(cxd56_audio_dnc_id_t id);

/**
 * @brief Disable DEQ
 *
 * @param[in] cxd56_audio_dnc_coef_t coef data
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_deq(FAR cxd56_audio_deq_coef_t *coef);


/**
 * @brief Disable DEQ
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_deq(void);

/**
 * @brief Enable BaseBand driver input
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_input(void);

/**
 * @brief Enable BaseBand driver output
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_output(void);

/**
 * @brief Disable BaseBand driver input
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_input(void);

/**
 * @brief Disable BaseBand driver output
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_output(void);

/**
 * @brief Set speaker output status
 *
 * @param[in] bool Whether speaker output is done or not
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_spout(bool sp_out_en);

/**
 * @brief Set volume
 *
 * @param[in] cxd56_audio_volid_t target volume device id
 * @param[in] int16_t volume[-1020:-102.0dB, ... 120:12.0dB]
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_vol(cxd56_audio_volid_t id, int16_t vol);

/**
 * @brief Mute volume
 *
 * @param[in] cxd56_audio_volid_t target volume device id
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_mute_vol(cxd56_audio_volid_t id);

/**
 * @brief Unmute volume
 *
 * @param[in] cxd56_audio_volid_t target volume device id
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_unmute_vol(cxd56_audio_volid_t id);

/**
 * @brief mute volume with fade-out
 *
 * @param[in] cxd56_audio_volid_t target volume device id
 * @param[in] bool wait fade-out end

 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_mute_vol_fade(cxd56_audio_volid_t id,
                                            bool wait);

/**
 * @brief unmute volume with fade-in
 *
 * @param[in] cxd56_audio_volid_t target volume device id
 * @param[in] bool wait fade-in end
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_unmute_vol_fade(cxd56_audio_volid_t id,
                                              bool wait);

/**
 * @brief Set beep frequency parameter
 *
 * @param[in] utin16_t beep frequency, 94:94Hz, ... 4085:4085Hz, step:1
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_beep_freq(uint16_t freq);

/**
 * @brief Set beep volume parameter
 *
 * @param[in] int16_t beep volume, -90:-90dB, ... 0:0dB, step:3, default:-12,
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_beep_vol(int16_t vol);

/**
 * @brief Play beep
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_play_beep(void);

/**
 * @brief Stop beep
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_stop_beep(void);

/**
 * @brief Set MIC gain
 *
 * @param[in] cxd56_audio_mic_gain_t* MIC gain[Analog:0~210[dB*10], Digital:-7850~0[dB*100]]
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_micgain(FAR cxd56_audio_mic_gain_t *gain);


/**
 * @brief Set DEQ table
 *
 * @param[in] bool  DEQ enable or disable
 * @param[in] cxd56_audio_deq_coef_t* coef table
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_deq(bool en, FAR cxd56_audio_deq_coef_t *deq);

/**
 * @brief Get dma handle
 *
 * @param[in]  cxd56_audio_dma_path_t dma path type
 * @param[out] cxd56_audio_dma_t* dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_get_dmahandle(cxd56_audio_dma_path_t path,
                                            FAR cxd56_audio_dma_t *handle);

/**
 * @brief Free dma handle
 *
 * @param[in]  cxd56_audio_dma_t Dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_free_dmahandle(FAR cxd56_audio_dma_t handle);

/**
 * @brief Set internal data path
 *
 * @param[in] cxd56_audio_signal_t Internal singal type
 * @param[in] cxd56_audio_sel_t Internal selector type
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_datapath(cxd56_audio_signal_t sig,
                                           cxd56_audio_sel_t sel);

/**
 * @brief Initialize dma transfer function
 *
 * @param[in]  cxd56_audio_dma_t      Dma handle
 * @param[in]  cxd56_audio_samp_fmt_t sampling data format 24bits or 16bits
 * @param[out] uint8_t*               Channel data numbers in DMA data
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_init_dma(cxd56_audio_dma_t handle,
                                       cxd56_audio_samp_fmt_t fmt,
                                       FAR uint8_t *ch_num);

/**
 * @brief Initialize dma transfer function
 *
 * @param[in] cxd56_audio_dma_t     Dma handle
 * @param[in] cxd56_audio_dma_cb_t  Call back function for notify dma state
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_dmacb(cxd56_audio_dma_t handle,
                                        FAR cxd56_audio_dma_cb_t cb);

/**
 * @brief Enable dma interrupt
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_dmaint(void);

/**
 * @brief Disable dma interrupt
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_dmaint(void);

/**
 * @brief Clear dma error interrupt state
 *
 * @param[in] cxd56_audio_dma_t  Dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_clear_dmaerrint(cxd56_audio_dma_t handle);

/**
 * @brief Mask dma error interrupt
 *
 * @param[in] cxd56_audio_dma_t  Dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_mask_dmaerrint(cxd56_audio_dma_t handle);

/**
 * @brief Unmask dma error interrupt
 *
 * @param[in] cxd56_audio_dma_t  Dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_unmask_dmaerrint(cxd56_audio_dma_t handle);

/**
 * @brief Start dma transfer
 *
 * @param[in] cxd56_audio_dma_t  Dma handle
 * @param[in] uint32_t  data address
 * @param[in] uint32_t  number of samples
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_start_dma(cxd56_audio_dma_t handle,
                                        uint32_t addr,
                                        uint32_t sample);

/**
 * @brief Stop dma transfer
 *
 * @param[in] cxd56_audio_dma_t  Dma handle
 *
 * @retval CXD56_AUDIO_ECODE return code
 */

CXD56_AUDIO_ECODE cxd56_audio_stop_dma(cxd56_audio_dma_t handle);

/**
 * @brief Set audio clock mode
 *
 * @param[in] cxd56_audio_clkmode_t  clock mode
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_clkmode(cxd56_audio_clkmode_t mode);

/**
 * @brief Get audio clock mode
 *
 * @param none
 *
 * @retval cxd56_audio_clkmode_t clock mode
 */
cxd56_audio_clkmode_t cxd56_audio_get_clkmode(void);

/**
 * @brief Get data format type of dma
 *
 * @param none
 *
 * @retval cxd56_audio_dmafmt_t clock mode
 */
cxd56_audio_dmafmt_t cxd56_audio_get_dmafmt(void);

/**
 * @brief Get mic device type
 *
 * @param none
 *
 * @retval cxd56_audio_micdev_t mic device type
 */
cxd56_audio_micdev_t cxd56_audio_get_micdev(void);

/**
 * @brief Enable digital soft ramp rate control
 *
 * @param[in] cxd56_audio_dsr_rate_t  Ramp rate
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_digsft(cxd56_audio_dsr_rate_t rate);

/**
 * @brief Disable digital soft ramp rate control
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_digsft(void);

/**
 * @brief Enable I2S I/O
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_en_i2s_io(void);

/**
 * @brief Disable I2S I/O
 *
 * @param none
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_dis_i2s_io(void);

/**
 * @brief Get audio driver status
 *
 * @param none
 *
 * @retval cxd56_audio_state_t value : current status
 */
cxd56_audio_state_t cxd56_audio_get_status(void);

/**
 * @brief Set audio speaker driver mode
 *
 * @param[in] cxd56_audio_sp_drv_t  speaker driver mode
 *
 * @retval CXD56_AUDIO_ECODE return code
 */
CXD56_AUDIO_ECODE cxd56_audio_set_spdriver(cxd56_audio_sp_drv_t sp_driver);

/**
 * @brief Get audio speaker driver mode
 *
 * @param none
 *
 * @retval cxd56_audio_sp_drv_t  speaker driver mode
 */
cxd56_audio_sp_drv_t cxd56_audio_get_spdriver(void);

#ifdef __cplusplus
} /* end of extern "C" */
#endif /* __cplusplus */

#endif /* __BSP_INCLUDE_ARCH_CHIP_CXD56_AUDIO_H */
/**
 * @}
 */
/**
 * @}
 */
