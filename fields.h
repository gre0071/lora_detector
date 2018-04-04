#ifndef _UR_FIELDS_H_
#define _UR_FIELDS_H_

/************* THIS IS AUTOMATICALLY GENERATED FILE, DO NOT EDIT *************/
#include <unirec/unirec.h>

#define F_RSSI   0
#define F_RSSI_T   double
#define F_SNR   1
#define F_SNR_T   double
#define F_BAD_WIDTH   2
#define F_BAD_WIDTH_T   uint32_t
#define F_CODE_RATE   3
#define F_CODE_RATE_T   uint32_t
#define F_FRQ   4
#define F_FRQ_T   uint32_t
#define F_RF_CHAIN   5
#define F_RF_CHAIN_T   uint32_t
#define F_RX_CHAIN   6
#define F_RX_CHAIN_T   uint32_t
#define F_SF   7
#define F_SF_T   uint32_t
#define F_SIZE   8
#define F_SIZE_T   uint32_t
#define F_US_COUNT   9
#define F_US_COUNT_T   uint32_t
#define F_APP_EUI   10
#define F_APP_EUI_T   char
#define F_APP_NONCE   11
#define F_APP_NONCE_T   char
#define F_DEV_ADDR   12
#define F_DEV_ADDR_T   char
#define F_DEV_EUI   13
#define F_DEV_EUI_T   char
#define F_DEV_NONCE   14
#define F_DEV_NONCE_T   char
#define F_FCNT   15
#define F_FCNT_T   char
#define F_FCTRL   16
#define F_FCTRL_T   char
#define F_FHDR   17
#define F_FHDR_T   char
#define F_F_OPTS   18
#define F_F_OPTS_T   char
#define F_F_PORT   19
#define F_F_PORT_T   char
#define F_FRM_PAYLOAD   20
#define F_FRM_PAYLOAD_T   char
#define F_GW_ID   21
#define F_GW_ID_T   char
#define F_LORA_PACKET   22
#define F_LORA_PACKET_T   char
#define F_MAC_PAYLOAD   23
#define F_MAC_PAYLOAD_T   char
#define F_MHDR   24
#define F_MHDR_T   char
#define F_MIC   25
#define F_MIC_T   char
#define F_MOD   26
#define F_MOD_T   char
#define F_NET_ID   27
#define F_NET_ID_T   char
#define F_NODE_MAC   28
#define F_NODE_MAC_T   char
#define F_PHY_PAYLOAD   29
#define F_PHY_PAYLOAD_T   char
#define F_STATUS   30
#define F_STATUS_T   char
#define F_UTC_TIME   31
#define F_UTC_TIME_T   char

extern uint16_t ur_last_id;
extern ur_static_field_specs_t UR_FIELD_SPECS_STATIC;
extern ur_field_specs_t ur_field_specs;

#endif

