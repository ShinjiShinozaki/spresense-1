/****************************************************************************
 * audio_player_objif/include/mem_layout.h
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

#ifndef MEM_LAYOUT_H_INCLUDED
#define MEM_LAYOUT_H_INCLUDED

/*
 * Memory devices
 */
/* AUD_SRAM: type=RAM, use=0x0003f300, remainder=0x00000d00 */
#define AUD_SRAM_ADDR  0x000c0000
#define AUD_SRAM_SIZE  0x00040000

/*
 * Fixed areas
 */
#define AUDIO_WORK_AREA_ALIGN   0x00000008
#define AUDIO_WORK_AREA_ADDR    0x000c0000
#define AUDIO_WORK_AREA_DRM     0x000c0000 /* _DRM is obsolete macro. to use _ADDR */
#define AUDIO_WORK_AREA_SIZE    0x0003e000

#define MSG_QUE_AREA_ALIGN   0x00000008
#define MSG_QUE_AREA_ADDR    0x000fe000
#define MSG_QUE_AREA_DRM     0x000fe000 /* _DRM is obsolete macro. to use _ADDR */
#define MSG_QUE_AREA_SIZE    0x00001000

#define MEMMGR_WORK_AREA_ALIGN   0x00000008
#define MEMMGR_WORK_AREA_ADDR    0x000ff000
#define MEMMGR_WORK_AREA_DRM     0x000ff000 /* _DRM is obsolete macro. to use _ADDR */
#define MEMMGR_WORK_AREA_SIZE    0x00000200

#define MEMMGR_DATA_AREA_ALIGN   0x00000008
#define MEMMGR_DATA_AREA_ADDR    0x000ff200
#define MEMMGR_DATA_AREA_DRM     0x000ff200 /* _DRM is obsolete macro. to use _ADDR */
#define MEMMGR_DATA_AREA_SIZE    0x00000100

/*
 * Memory Manager max work area size
 */
#define MEMMGR_MAX_WORK_SIZE  0x000000e4

/*
 * Pool IDs
 */
#define NULL_POOL  0
#define DEC_ES_MAIN_BUF_POOL  1
#define REND_PCM_BUF_POOL  2
#define DEC_APU_CMD_POOL  3
#define SRC_WORK_BUF_POOL  4
#define PF0_PCM_BUF_POOL  5
#define PF1_PCM_BUF_POOL  6
#define PF0_APU_CMD_POOL  7
#define PF1_APU_CMD_POOL  8

#define NUM_MEM_LAYOUTS  1
#define NUM_MEM_POOLS  9


/*
 * Pool areas
 */
/* Layout0: */
#define MEMMGR_L0_WORK_SIZE   0x000000e4

/* Skip 0x0004 bytes for alignment. */
#define L0_DEC_ES_MAIN_BUF_POOL_ALIGN    0x00000008
#define L0_DEC_ES_MAIN_BUF_POOL_L_FENCE  0x000c0004
#define L0_DEC_ES_MAIN_BUF_POOL_ADDR     0x000c0008
#define L0_DEC_ES_MAIN_BUF_POOL_SIZE     0x00006000
#define L0_DEC_ES_MAIN_BUF_POOL_U_FENCE  0x000c6008
#define L0_DEC_ES_MAIN_BUF_POOL_NUM_SEG  0x00000004
#define L0_DEC_ES_MAIN_BUF_POOL_SEG_SIZE 0x00001800

#define L0_REND_PCM_BUF_POOL_ALIGN    0x00000008
#define L0_REND_PCM_BUF_POOL_L_FENCE  0x000c600c
#define L0_REND_PCM_BUF_POOL_ADDR     0x000c6010
#define L0_REND_PCM_BUF_POOL_SIZE     0x00012048
#define L0_REND_PCM_BUF_POOL_U_FENCE  0x000d8058
#define L0_REND_PCM_BUF_POOL_NUM_SEG  0x00000009
#define L0_REND_PCM_BUF_POOL_SEG_SIZE 0x00002008

#define L0_DEC_APU_CMD_POOL_ALIGN    0x00000008
#define L0_DEC_APU_CMD_POOL_L_FENCE  0x000d805c
#define L0_DEC_APU_CMD_POOL_ADDR     0x000d8060
#define L0_DEC_APU_CMD_POOL_SIZE     0x00000398
#define L0_DEC_APU_CMD_POOL_U_FENCE  0x000d83f8
#define L0_DEC_APU_CMD_POOL_NUM_SEG  0x0000000a
#define L0_DEC_APU_CMD_POOL_SEG_SIZE 0x0000005c

#define L0_SRC_WORK_BUF_POOL_ALIGN    0x00000008
#define L0_SRC_WORK_BUF_POOL_L_FENCE  0x000d83fc
#define L0_SRC_WORK_BUF_POOL_ADDR     0x000d8400
#define L0_SRC_WORK_BUF_POOL_SIZE     0x00002000
#define L0_SRC_WORK_BUF_POOL_U_FENCE  0x000da400
#define L0_SRC_WORK_BUF_POOL_NUM_SEG  0x00000001
#define L0_SRC_WORK_BUF_POOL_SEG_SIZE 0x00002000

#define L0_PF0_PCM_BUF_POOL_ALIGN    0x00000008
#define L0_PF0_PCM_BUF_POOL_L_FENCE  0x000da404
#define L0_PF0_PCM_BUF_POOL_ADDR     0x000da408
#define L0_PF0_PCM_BUF_POOL_SIZE     0x00002008
#define L0_PF0_PCM_BUF_POOL_U_FENCE  0x000dc410
#define L0_PF0_PCM_BUF_POOL_NUM_SEG  0x00000001
#define L0_PF0_PCM_BUF_POOL_SEG_SIZE 0x00002008

#define L0_PF1_PCM_BUF_POOL_ALIGN    0x00000008
#define L0_PF1_PCM_BUF_POOL_L_FENCE  0x000dc414
#define L0_PF1_PCM_BUF_POOL_ADDR     0x000dc418
#define L0_PF1_PCM_BUF_POOL_SIZE     0x00002008
#define L0_PF1_PCM_BUF_POOL_U_FENCE  0x000de420
#define L0_PF1_PCM_BUF_POOL_NUM_SEG  0x00000001
#define L0_PF1_PCM_BUF_POOL_SEG_SIZE 0x00002008

#define L0_PF0_APU_CMD_POOL_ALIGN    0x00000008
#define L0_PF0_APU_CMD_POOL_L_FENCE  0x000de424
#define L0_PF0_APU_CMD_POOL_ADDR     0x000de428
#define L0_PF0_APU_CMD_POOL_SIZE     0x00000398
#define L0_PF0_APU_CMD_POOL_U_FENCE  0x000de7c0
#define L0_PF0_APU_CMD_POOL_NUM_SEG  0x0000000a
#define L0_PF0_APU_CMD_POOL_SEG_SIZE 0x0000005c

#define L0_PF1_APU_CMD_POOL_ALIGN    0x00000008
#define L0_PF1_APU_CMD_POOL_L_FENCE  0x000de7c4
#define L0_PF1_APU_CMD_POOL_ADDR     0x000de7c8
#define L0_PF1_APU_CMD_POOL_SIZE     0x00000398
#define L0_PF1_APU_CMD_POOL_U_FENCE  0x000deb60
#define L0_PF1_APU_CMD_POOL_NUM_SEG  0x0000000a
#define L0_PF1_APU_CMD_POOL_SEG_SIZE 0x0000005c

/* Remainder AUDIO_WORK_AREA=0x0001f49c */

#endif /* MEM_LAYOUT_H_INCLUDED */
