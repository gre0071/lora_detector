/************* THIS IS AUTOMATICALLY GENERATED FILE, DO NOT EDIT *************/
// Tables are indexed by field ID
#include "fields.h"

char *ur_field_names_static[] = {
   "RSSI",
   "SNR",
   "BAD_WIDTH",
   "CODE_RATE",
   "FRQ",
   "RF_CHAIN",
   "RX_CHAIN",
   "SF",
   "SIZE",
   "US_COUNT",
   "APP_EUI",
   "APP_NONCE",
   "DEV_ADDR",
   "DEV_EUI",
   "DEV_NONCE",
   "FCNT",
   "FCTRL",
   "FHDR",
   "F_OPTS",
   "F_PORT",
   "FRM_PAYLOAD",
   "GW_ID",
   "LORA_PACKET",
   "MAC_PAYLOAD",
   "MHDR",
   "MIC",
   "MOD",
   "NET_ID",
   "NODE_MAC",
   "PHY_PAYLOAD",
   "STATUS",
   "UTC_TIME",
};
short ur_field_sizes_static[] = {
   8, /* RSSI */
   8, /* SNR */
   4, /* BAD_WIDTH */
   4, /* CODE_RATE */
   4, /* FRQ */
   4, /* RF_CHAIN */
   4, /* RX_CHAIN */
   4, /* SF */
   4, /* SIZE */
   4, /* US_COUNT */
   -1, /* APP_EUI */
   -1, /* APP_NONCE */
   -1, /* DEV_ADDR */
   -1, /* DEV_EUI */
   -1, /* DEV_NONCE */
   -1, /* FCNT */
   -1, /* FCTRL */
   -1, /* FHDR */
   -1, /* F_OPTS */
   -1, /* F_PORT */
   -1, /* FRM_PAYLOAD */
   -1, /* GW_ID */
   -1, /* LORA_PACKET */
   -1, /* MAC_PAYLOAD */
   -1, /* MHDR */
   -1, /* MIC */
   -1, /* MOD */
   -1, /* NET_ID */
   -1, /* NODE_MAC */
   -1, /* PHY_PAYLOAD */
   -1, /* STATUS */
   -1, /* UTC_TIME */
};
ur_field_type_t ur_field_types_static[] = {
   UR_TYPE_DOUBLE, /* RSSI */
   UR_TYPE_DOUBLE, /* SNR */
   UR_TYPE_UINT32, /* BAD_WIDTH */
   UR_TYPE_UINT32, /* CODE_RATE */
   UR_TYPE_UINT32, /* FRQ */
   UR_TYPE_UINT32, /* RF_CHAIN */
   UR_TYPE_UINT32, /* RX_CHAIN */
   UR_TYPE_UINT32, /* SF */
   UR_TYPE_UINT32, /* SIZE */
   UR_TYPE_UINT32, /* US_COUNT */
   UR_TYPE_STRING, /* APP_EUI */
   UR_TYPE_STRING, /* APP_NONCE */
   UR_TYPE_STRING, /* DEV_ADDR */
   UR_TYPE_STRING, /* DEV_EUI */
   UR_TYPE_STRING, /* DEV_NONCE */
   UR_TYPE_STRING, /* FCNT */
   UR_TYPE_STRING, /* FCTRL */
   UR_TYPE_STRING, /* FHDR */
   UR_TYPE_STRING, /* F_OPTS */
   UR_TYPE_STRING, /* F_PORT */
   UR_TYPE_STRING, /* FRM_PAYLOAD */
   UR_TYPE_STRING, /* GW_ID */
   UR_TYPE_STRING, /* LORA_PACKET */
   UR_TYPE_STRING, /* MAC_PAYLOAD */
   UR_TYPE_STRING, /* MHDR */
   UR_TYPE_STRING, /* MIC */
   UR_TYPE_STRING, /* MOD */
   UR_TYPE_STRING, /* NET_ID */
   UR_TYPE_STRING, /* NODE_MAC */
   UR_TYPE_STRING, /* PHY_PAYLOAD */
   UR_TYPE_STRING, /* STATUS */
   UR_TYPE_STRING, /* UTC_TIME */
};
ur_static_field_specs_t UR_FIELD_SPECS_STATIC = {ur_field_names_static, ur_field_sizes_static, ur_field_types_static, 32};
ur_field_specs_t ur_field_specs = {ur_field_names_static, ur_field_sizes_static, ur_field_types_static, 32, 32, 32, NULL, UR_UNINITIALIZED};
