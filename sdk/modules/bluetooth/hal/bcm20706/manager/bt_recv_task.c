/****************************************************************************
 * modules/bluetooth/hal/bcm20706/manager/bt_recv_task.c
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

#include <stdio.h>
#include <pthread.h>
#include <debug.h>
#include <bt/bt_comm.h>
#include <bt/bt_a2dp_sink.h>
#include <bt/bt_avrc_tar.h>
#include <bt/bt_avrc_con.h>
#include <ble/ble_comm.h>
#include <arch/board/board.h>

#include "manager/bt_freq_lock.h"
#include "manager/bt_uart_manager.h"
#include "bt_util.h"
#include "bt_debug.h"
#include "bcm20706_ble_internal.h"
#include "bcm20706_bt_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DBG_LOG_DEBUG btdbg
#define DBG_LOG_ERROR btdbg

#define HANDLE_SIZE    2
#define BT_RESULT_SIZE 2
#define NVRAM_ID_LEN   2
#define HASH_POS_IN_VERSION 8

/****************************************************************************
 * Private Data
 ****************************************************************************/

static pthread_t gRecvTask;
static BT_EVT bt_evt_buff;
uint8_t *appEvtBuff = (uint8_t *) &bt_evt_buff;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void btRecvDeviceStatus(uint8_t *p, uint16_t len, int group)
{
  struct bt_event_cmd_stat_t cmd_stat_evt;
  
  memcpy(&cmd_stat_evt.cmd_status, p,  MIN(len, BT_EVT_DATA_LEN));

  switch (group)
    {
      case BT_CONTROL_GROUP_DEVICE:
        cmd_stat_evt.group_id = BT_GROUP_COMMON;
        cmd_stat_evt.event_id = BT_COMMON_EVENT_CMD_STATUS;
        bt_common_event_handler((struct bt_event_t *) &cmd_stat_evt);
        break;

      case BT_CONTROL_GROUP_HF:
        cmd_stat_evt.group_id = BT_GROUP_HFP;
        cmd_stat_evt.event_id = BT_HFP_EVENT_CMD_STATUS;
        bt_hfp_event_handler((struct bt_event_t *) &cmd_stat_evt);
        break;

      case BT_CONTROL_GROUP_AVRC_TARGET:
      case BT_CONTROL_GROUP_AVRC_CONTROLLER:
        cmd_stat_evt.group_id = BT_GROUP_AVRCP;
        cmd_stat_evt.event_id = BT_AVRCP_EVENT_CMD_STATUS;
        bt_avrcp_event_handler((struct bt_event_t *) &cmd_stat_evt);
        break;

      case BT_CONTROL_GROUP_A2DP_SINK:
      case BT_CONTROL_GROUP_AUDIO_SINK:
        cmd_stat_evt.group_id = BT_GROUP_A2DP;
        cmd_stat_evt.event_id = BT_A2DP_EVENT_CMD_STATUS;
        bt_a2dp_event_handler((struct bt_event_t *) &cmd_stat_evt);
        break;

      default:
        break;
    }
}

static void btSaveBondInfo(BT_ADDR *addr)
{
  BLE_GapBondInfo info = {0};

  info.addrType = 0; /* Only use in BLE */
  memcpy(info.addr, addr, BT_ADDR_LEN);

  BLE_GapSaveBondInfo(&info);
}

static void btRecvBondInfo(uint8_t *p, uint16_t len)
{
  uint8_t *rp = NULL;
  struct bt_event_bond_info_t bond_info_evt;

  /* Copy target device address */
  rp = p + NVRAM_ID_LEN;
  memcpy(&bond_info_evt.addr, rp, BT_ADDR_LEN);

  bond_info_evt.group_id = BT_GROUP_COMMON;
  bond_info_evt.event_id = BT_COMMON_EVENT_BOND_INFO;

  /* Save bonding information to filesystem */
  btSaveBondInfo(&bond_info_evt.addr);

  bt_common_event_handler((struct bt_event_t *) &bond_info_evt);
}

static void recevNvramData(uint8_t evtCode, uint8_t *p, uint16_t len)
{
  uint8_t *wp = NULL;
  ble_evt_t *pBleBcmEvt = (ble_evt_t*)p;
  wp = appEvtBuff;
  UINT16_TO_STREAM(wp,(BT_CONTROL_GROUP_DEVICE<< 8) | evtCode);

  btdbg("receive nv data,transport = %d, len = %d\n", p[len-1], len);
  if (p[len - 1] == BT_TRANSPORT_BR_EDR)
    {
      btdbg("BT key type = %02x, key = %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, \
          %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n",
          p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15], p[16], p[17], p[18],
          p[19], p[20], p[21], p[22], p[23], p[24]);
      bleRecvNvramData(pBleBcmEvt, len);
      btdbg("receive NV data.\n");
      btRecvBondInfo(p, len);
      btdbg("receive bond information.\n");
    }
  else if (p[len - 1] == BT_TRANSPORT_LE)
    {
      bleRecvNvramData(pBleBcmEvt, len);
      btdbg("BLE ltk = %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, \
          %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n",
          p[52], p[53], p[54], p[55], p[56], p[57], p[58], p[59], p[60], p[61],
          p[62], p[63], p[64], p[65], p[66], p[67]);
    }
}

static void btRecvInquiryResult(uint8_t *p, uint16_t len)
{
#define RSSI_LEN 1
#define TYPE_COMPLETE_NAME 0x09
  uint8_t *rp = NULL;
  uint8_t value_length = 0;
  uint8_t type_id = 0;
  struct bt_event_inquiry_rslt_t inq_rslt_evt;

  /* Get target device address */

  rp = p;
  memcpy(&inq_rslt_evt.addr, rp, BT_ADDR_LEN);

  rp += BT_ADDR_LEN;
  rp += BT_CLASS_LEN;
  rp += RSSI_LEN;

  /* Value length(contain '0') */

  STREAM_TO_UINT8(value_length, rp);

  /* Value type */

  STREAM_TO_UINT8(type_id, rp);

  if (type_id == TYPE_COMPLETE_NAME)
    {
      memcpy(inq_rslt_evt.name, rp, value_length);

      /* Insert '\0' at the end of name */

      inq_rslt_evt.name[value_length - 1] = '\0';
    }
  else
    {
      /* If type ID is not Complete name ID, return null */

      inq_rslt_evt.name[0] = '\0';
    }

  inq_rslt_evt.group_id = BT_GROUP_COMMON;
  inq_rslt_evt.event_id = BT_COMMON_EVENT_INQUIRY_RESULT;

  bt_common_event_handler((struct bt_event_t *) &inq_rslt_evt);
}

static void btRecvInquiryComplete(uint8_t *p, uint16_t len)
{
  struct bt_event_t bt_evt;

  bt_evt.group_id = BT_GROUP_COMMON;
  bt_evt.event_id = BT_COMMON_EVENT_INQUIRY_COMPLETE;

  bt_common_event_handler((struct bt_event_t *) &bt_evt);
}

static void pairingComplete(uint8_t evtCode, uint8_t *p)
{
  struct bt_event_pair_cmplt_t pair_cmplt_evt;
  ble_evt_t *pBleBcmEvt = (ble_evt_t*)p;

  btdbg("pair complete,status = %x, addr = %x,%x, %x, %x, %x, %x, transport = %x\n",
      p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);

  if (((pair_result_t*)p)->transport == BT_TRANSPORT_BR_EDR)
    {
      memcpy(&pair_cmplt_evt.status, p, sizeof(uint8_t));
      p += sizeof(uint8_t);
      STREAM_TO_BDADDR(&pair_cmplt_evt.addr, p);
    }
  else if (((pair_result_t*)p)->transport == BT_TRANSPORT_LE)
    {
      bleRecvAuthStatus(pBleBcmEvt);
    }

  pair_cmplt_evt.group_id = BT_GROUP_COMMON;
  pair_cmplt_evt.event_id = BT_COMMON_EVENT_PAIRING_COMPLETE;

  bt_common_event_handler((struct bt_event_t *) &pair_cmplt_evt);
}

static void btRecvConnDevName(uint8_t evtCode, uint8_t *p)
{
  struct bt_event_dev_name_t dev_name_evt;

  /* Skip status */

  p += 2;

  /* Skip address */

  p += BT_ADDR_LEN;

  /* Copy device name */

  strncpy(dev_name_evt.name, (const char*)p, BT_MAX_NAME_LEN - 1);
  dev_name_evt.name[BT_MAX_NAME_LEN - 1] = '\0';

  dev_name_evt.group_id = BT_GROUP_COMMON;
  dev_name_evt.event_id = BT_COMMON_EVENT_CONN_DEV_NAME;

  bt_common_event_handler((struct bt_event_t *) &dev_name_evt);
}

static void btRecvUserConfirmation(uint8_t *ptr)
{
  BT_REPLY_CONFIRM btReplyConfirm;
  uint8_t buff[BT_SHORT_COMMAND_LEN] = {0};
  uint8_t *p = buff;
  uint8_t *rp = NULL;
  uint8_t *wp = ((BT_EVT *)appEvtBuff)->evtData;
  BT_EVT_CONFIRMATION_REQ *tncqEvt = (BT_EVT_CONFIRMATION_REQ *)wp;

  /* Get target address */

  rp = ptr;
  memcpy(&tncqEvt->addr, rp, BT_ADDR_LEN);

  /* Get numeric */

  rp += BT_ADDR_LEN;
  memcpy(&tncqEvt->numeric, rp, sizeof(tncqEvt->numeric));

  /* Infuture, will send event to application */

  memcpy(&btReplyConfirm.addr, &tncqEvt->addr, BT_ADDR_LEN);
  btReplyConfirm.btAccept = BT_TRUE;

  /* Send accept command */

  UINT8_TO_STREAM(p, PACKET_CONTROL);
  UINT16_TO_STREAM(p, BT_CONTROL_COMMAND_REPLY_CONFIRMATION);
  UINT16_TO_STREAM(p, 7);
  memcpy(p, &btReplyConfirm.addr, BT_ADDR_LEN);
  p += BT_ADDR_LEN;
  UINT8_TO_STREAM(p, btReplyConfirm.btAccept);
  btUartSendData(buff, p - buff);
}

static void btRecvAclConnStatus(uint8_t *p, uint16_t len)
{
  struct bt_event_conn_stat_t con_stat_evt;
  uint8_t connect;
  uint8_t type;
  uint8_t reason;

  /* Copy device address */

  memcpy(&con_stat_evt.addr, p, sizeof(BT_ADDR));

  /* Copy connect status */

  p += sizeof(BT_ADDR);
  memcpy(&connect, p, sizeof(uint8_t));
  con_stat_evt.connected = connect == 1;

  /* Copy type */

  p += sizeof(uint8_t);
  memcpy(&type, p, sizeof(uint8_t));

  /* Copy reason */

  p += sizeof(uint8_t);
  memcpy(&reason, p, sizeof(uint8_t));
  con_stat_evt.status = reason;

  con_stat_evt.group_id = BT_GROUP_COMMON;
  con_stat_evt.event_id = BT_COMMON_EVENT_CONN_STAT_CHANGE;

  btdbg("addr: %02x.%02x.%02x.%02x.%02x,%02x is connect:%d,"
      "transport type: %x, disconnect reason: %x.\n",
    con_stat_evt.addr.address[0], con_stat_evt.addr.address[1],
    con_stat_evt.addr.address[2], con_stat_evt.addr.address[3],
    con_stat_evt.addr.address[4], con_stat_evt.addr.address[5],
    connect, type, reason);

  bt_common_event_handler((struct bt_event_t *) &con_stat_evt);
}

static void bleRecvSecurityRequest(BLE_Evt *pBleEvent, ble_evt_t *pBleBcmEvt)
{
  uint8_t *rp     = pBleBcmEvt->evtData;
  BT_ADDR bleAddr = {{0}};
  BLE_GapPairingFeature pfeature;

  /* Setup security feature */

  pfeature.oob        = BLE_GAP_OOB_AUTH_DATA_NOT_PRESENT;
  pfeature.ioCap      = BLE_GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
  pfeature.authReq    = BLE_GAP_AUTH_REQ_NO_MITM_BOND;
  pfeature.minKeySize = BLE_GAP_MIN_KEY_SIZE;
  pfeature.maxKeySize = BLE_GAP_MAX_KEY_SIZE;

  btdbg("notify addr = %x,%x,%x,%x,%x,%x\n",rp[0],rp[1],rp[2],rp[3],rp[4],rp[5]);
  memcpy(&bleAddr, rp, BT_ADDR_LEN);

  /* Reply security feature */

  bleGapReplySecurity(bleAddr, BLE_ENABLE, pfeature);
}

static void btRecvSppEvtConnected(uint8_t *p)
{
  struct bt_spp_event_connect_t connect_evt;

  /* Copy device address */

  memcpy(&connect_evt.addr, p, BT_ADDR_LEN);

  /* Copy Handle ID */

  p += BT_ADDR_LEN;
  STREAM_TO_UINT16(connect_evt.handle, p);

  connect_evt.group_id = BT_GROUP_SPP;
  connect_evt.event_id = BT_SPP_EVENT_CONNECT;

  bt_spp_event_handler((struct bt_event_t *) &connect_evt);
}

static void btRecvSppEvtDisconnect(uint8_t *p)
{
  struct bt_spp_event_connect_t connect_evt;

  connect_evt.group_id = BT_GROUP_SPP;
  connect_evt.event_id = BT_SPP_EVENT_DISCONNECT;

  bt_spp_event_handler((struct bt_event_t *) &connect_evt);
}

static void btRecvSppEvtRxData(uint8_t *p, uint16_t len)
{
  struct bt_spp_event_recv_data_t recv_evt;
  uint16_t handle = 0;

  /* Get handle ID */

  STREAM_TO_UINT16(handle, p);
  (void) handle;

  /* Get data length */
  len = MIN(len, BT_EVT_DATA_LEN);
  recv_evt.len = len - HANDLE_SIZE;

  /* Get data body */
  memcpy(recv_evt.data, p, recv_evt.len);

  recv_evt.group_id = BT_GROUP_SPP;
  recv_evt.event_id = BT_SPP_EVENT_RX_DATA;

  bt_spp_event_handler((struct bt_event_t *) &recv_evt);
}

void bleRecvLeConnected(BLE_Evt *bleEvent, ble_evt_t *pBleBcmEvt)
{
  struct ble_event_conn_stat_t conn_stat_evt;
  uint8_t *rp = NULL;

  rp = pBleBcmEvt->evtData + BT_ADDR_LEN + 1;
  STREAM_TO_UINT16(conn_stat_evt.handle, rp);
  btdbg("connect handle = %d\n", conn_stat_evt.handle);
  rp = pBleBcmEvt->evtData + 1;
  btdbg("connect addr = %x,%x,%x,%x,%x,%x\n",rp[0],rp[1],rp[2],rp[3],rp[4],rp[5]);
  memcpy(&conn_stat_evt.addr, rp, sizeof(BT_ADDR));

  conn_stat_evt.connected = true;

  conn_stat_evt.group_id = BLE_GROUP_COMMON;
  conn_stat_evt.event_id = BLE_COMMON_EVENT_CONN_STAT_CHANGE;

  ble_common_event_handler((struct bt_event_t *) &conn_stat_evt);
}

void bleRecvLeDisconnected(BLE_Evt *pBleEvent, ble_evt_t *pBleBcmEvt)
{
  struct ble_event_conn_stat_t conn_stat_evt;

  conn_stat_evt.connected = false;

  conn_stat_evt.group_id = BLE_GROUP_COMMON;
  conn_stat_evt.event_id = BLE_COMMON_EVENT_CONN_STAT_CHANGE;

  ble_common_event_handler((struct bt_event_t *) &conn_stat_evt);
}

void bleRecvGattReadRequest(BLE_Evt *pBleEvent, ble_evt_t *pBleBcmEvt)
{
  /* Read request will operate by firmware side */
  /* nop */
}

void bleRecvGattWriteRequest(BLE_Evt *pBleEvent,
    ble_evt_t *pBleBcmEvt, uint16_t len)
{
  struct ble_gatt_event_write_req_t write_req_evt;
  uint8_t *rp = NULL;
  uint16_t conn_handle;

  /* Get characteristic handle ID */
  rp = pBleBcmEvt->evtData;
  STREAM_TO_UINT16(conn_handle, rp);
  STREAM_TO_UINT16(write_req_evt.char_handle, rp);
  (void) conn_handle;

  /* Get length of data */
  write_req_evt.length = len - BLE_HANDLE_LEN - BLE_HANDLE_LEN;

  /* Get data body */
  memcpy(write_req_evt.data, rp, MAX_RCV_DATA_LENGTH);

  /* This HAL doesn't support service handle ID while write request */

  write_req_evt.serv_handle = BLE_GATT_INVALID_SERVICE_HANDLE;

  write_req_evt.group_id = BLE_GROUP_GATT;
  write_req_evt.event_id = BLE_GATT_EVENT_WRITE_REQ;

  ble_gatt_event_handler((struct bt_event_t *) &write_req_evt);
}

/* Event spliter */

static void btRecvDeviceControlPacket(uint8_t evtCode, uint8_t *p,
    uint16_t len)
{
  uint8_t *wp = NULL;
  BLE_Evt *bleEvent = &(((BLE_EvtCtx*)appEvtBuff)->evt);
  ble_evt_t *pBleBcmEvt = (ble_evt_t*)p;

  wp = appEvtBuff;
  UINT16_TO_STREAM(wp,(BT_CONTROL_GROUP_DEVICE<< 8) | evtCode);

  switch (evtCode)
    {
      case BT_CONTROL_EVENT_COMMAND_STATUS:
        btRecvDeviceStatus(p, len, BT_CONTROL_GROUP_DEVICE);
        break;

      case BT_CONTROL_EVENT_NVRAM_DATA:
        recevNvramData(evtCode, p, len);
        break;

      case BT_CONTROL_EVENT_INQUIRY_RESULT:
        btRecvInquiryResult(p, len);
        break;

      case BT_CONTROL_EVENT_INQUIRY_COMPLETE:
        btRecvInquiryComplete(p,len);
        break;

      case BT_CONTROL_EVENT_PAIRING_COMPLETE:
        pairingComplete(evtCode, p);
        break;

      case BT_EVT_DEV_CONNECTED_DEVICE_NAME:
        btRecvConnDevName(evtCode, p);
        break;
      case BT_CONTROL_EVENT_USER_CONFIRMATION:
        btRecvUserConfirmation(p);
        break;

      case BT_EVT_DEV_ACL_CONNECTION_STATUS:
        btRecvAclConnStatus(p, len);
        break;

      case BT_CONTROL_EVENT_SECURITY_REQUEST:
        btdbg("security request\n");
        bleRecvSecurityRequest(bleEvent, pBleBcmEvt);
        break;

      case BT_CONTROL_EVENT_USER_PASSKEY:
      case BT_CONTROL_EVENT_REPLY_BT_VERSION:
      case BT_CONTROL_EVENT_DEVICE_STARTED:
      case BT_CONTROL_EVENT_WICED_TRACE:
      case BT_CONTROL_EVENT_HCI_TRACE:
      case BT_CONTROL_EVENT_ENCRYPTION_CHANGED:
      case BT_CONTROL_EVENT_PASSKEY_NOTIFICATION:
      case BT_CONTROL_EVENT_POWER_MANAGER_STATUS:
      case BT_CONTROL_EVENT_REQUEST_FEATURE:
      case BT_CONTROL_EVENT_REPLY_BAUD_RATE:
      case BT_CONTROL_EVENT_REPLY_I2S_ROLE:
      case BT_CONTROL_EVENT_REPLY_VENDORID:
        /* Not supported yet */
        break;

      default:
        break;
    }
}

static void btRecvSppControlPacket(uint8_t evtCode, uint8_t *p, uint16_t len)
{
  uint8_t *wp = NULL;

  wp = appEvtBuff;
  UINT16_TO_STREAM(wp, ((BT_CONTROL_GROUP_SPP << 8) | evtCode));
  switch (evtCode)
    {
      case BT_CONTROL_SPP_EVENT_CONNECTED:
        btRecvSppEvtConnected(p);
        break;

      case BT_CONTROL_SPP_EVENT_DISCONNECTED:
        btRecvSppEvtDisconnect(p);
        break;

      case BT_CONTROL_SPP_EVENT_CONNECTION_FAILED:
        /* Not supported yet */
        break;

      case BT_CONTROL_SPP_EVENT_RX_DATA:
        btRecvSppEvtRxData(p, len);
        break;

      case BT_CONTROL_SPP_EVENT_SERVICE_NOT_FOUND:
      case BT_CONTROL_SPP_EVENT_TX_COMPLETE:
      case BT_CONTROL_SPP_EVENT_STATUS:
        /* Not supported yet */
        break;

      default:
        break;
    }
}

void bleRecvLeControlPacket(uint8_t evtCode, uint8_t *p, uint16_t len)
{
  BLE_Evt *bleEvent = &(((BLE_EvtCtx*)appEvtBuff)->evt);
  ble_evt_t *pBleBcmEvt = (ble_evt_t*)p;

  switch (evtCode)
    {
      case BT_CONTROL_LE_EVENT_CONNECTED:
        bleRecvLeConnected(bleEvent, pBleBcmEvt);
        btdbg("ble connect\n");
        break;
      case BT_CONTROL_LE_EVENT_DISCONNECTED:
        bleRecvLeDisconnected(bleEvent, pBleBcmEvt);
        btdbg("ble disconnect\n");
        break;
      case BT_CONTROL_LE_EVENT_ADVERTISEMENT_REPORT:
      case BT_CONTROL_LE_EVENT_ADVERTISEMENT_STATE:
      case BT_CONTROL_LE_EVENT_SCAN_STATUS:
      case BT_CONTROL_LE_EVENT_CONN_PARAMS:
      case BT_CONTROL_LE_EVENT_CONNECT_TIMEOUT:
      case BT_CONTROL_LE_EVENT_COMMAND_STATUS:
        break;
      default:
        break;
    }
}

void bleRecvGattControlPacket(uint8_t evtCode, uint8_t *p, uint16_t len)
{
  BLE_Evt *bleEvent = &(((BLE_EvtCtx*)appEvtBuff)->evt);
  ble_evt_t *pBleBcmEvt = (ble_evt_t*)p;

  switch (evtCode)
    {
      case BT_CONTROL_GATT_EVENT_READ_REQUEST:
        bleRecvGattReadRequest(bleEvent, pBleBcmEvt);
        break;

      case BT_CONTROL_GATT_EVENT_WRITE_REQUEST:
        bleRecvGattWriteRequest(bleEvent, pBleBcmEvt, len);
        break;

      case BT_CONTROL_GATT_EVENT_COMMAND_STATUS:
      case BT_CONTROL_GATT_EVENT_DISCOVERY_COMPLETE:
      case BT_CONTROL_GATT_EVENT_SERVICE_DISCOVERED:
      case BT_CONTROL_GATT_EVENT_CHARACTERISTIC_DISCOVERED:
      case BT_CONTROL_GATT_EVENT_DESCRIPTOR_DISCOVERED:
      case BT_CONTROL_GATT_EVENT_READ_RESPONSE:
      case BT_CONTROL_GATT_EVENT_WRITE_RESPONSE:
      case BT_CONTROL_GATT_EVENT_WRITE_COMPLETE:
      case BT_CONTROL_GATT_EVENT_INDICATION:
      case BT_CONTROL_GATT_EVENT_NOTIFICATION:
        /* Not supported yet */
        break;

      default:
        break;
    }
}

static void btRecvControlPacket(uint16_t opcode, uint8_t *p, uint16_t len)
{
  uint8_t evtCode = (opcode)&0xff;

  switch (opcode >> 8)
    {
      case BT_CONTROL_GROUP_DEVICE:
        btRecvDeviceControlPacket(evtCode, p, len);
        break;

      case BT_CONTROL_GROUP_HF:
        /* Not supported yet */
        break;

      case BT_CONTROL_GROUP_LE:
        bleRecvLeControlPacket(evtCode, p, len);
        break;

      case BT_CONTROL_GROUP_GATT:
        bleRecvGattControlPacket(evtCode, p, len);
        break;

      case BT_CONTROL_GROUP_SPP:
        btRecvSppControlPacket(evtCode, p, len);
        break;

      case BT_CONTROL_GROUP_AVRC_TARGET:
        /* Not supported yet */
        break;

      case BT_CONTROL_GROUP_AVRC_CONTROLLER:
        /* Not supported yet */
        break;

      case BT_CONTROL_GROUP_A2DP_SINK:
        /* Not supported yet */
        break;

      case BT_CONTROL_GROUP_AUDIO_SINK:
        /* Not supported yet */
        break;

      case BT_CONTROL_GROUP_A2DP_SRC:
      case BT_CONTROL_GROUP_AG:
        /* nop */
        break;

      default:
        break;

    }
}

static void* btRecvTaskSingleStep(void *param)
{
  uint8_t *p = NULL;
  uint16_t opcode = 0;
  uint16_t packetLen = 0;

  while (true)
    {
      p = btUartGetCompleteBuff(&packetLen);
      if (p == NULL)
        {
          break;
        }
      switch (*p++)
        {
          case PACKET_CONTROL:
            STREAM_TO_UINT16(opcode, p);
            STREAM_TO_UINT16(packetLen, p);
            btRecvControlPacket(opcode, p, packetLen);
            break;

          case PACKET_MEDIA:
            /* nop */
            break;

          case PACKET_HCI:
            /* nop */
            break;

          default:
            break;
        }
      btUartReleaseCompleteBuff();
    }

  return NULL;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: btRecvTaskEntry
 *
 * Description:
 *   Start receive thread to get data from target.
 *
 ****************************************************************************/

int btRecvTaskEntry(void)
{
  int errCode =  BT_SUCCESS;
  errCode = pthread_create(&gRecvTask, NULL, btRecvTaskSingleStep, NULL);

  if (errCode)
    {
      errCode = -ENXIO;
    }

  return errCode;
}

/****************************************************************************
 * Name: btRecvTaskEnd
 *
 * Description:
 *   Stop receive thread to get data from target.
 *
 ****************************************************************************/

int btRecvTaskEnd(void)
{
  int ret = 0;

  ret = pthread_cancel(gRecvTask);

  if (ret != 0)
    {
      btdbg("Receive task cancel error.\n");
    }

  ret = pthread_join(gRecvTask, NULL);

  if (ret != 0)
    {
      btdbg("Receive task finalize error.\n");
    }

  return ret;
}
