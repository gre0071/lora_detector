/**
 * \file example_module.c
 * \brief Example of NEMEA module.
 * \author Vaclav Bartos <ibartosv@fit.vutbr.cz>
 * \author Marek Svepes <svepemar@fit.cvut.cz>
 * \author Jaroslav Hlavac <hlavaj20@fit.cvut.cz>
 * \date 2016
 */
/*
 * Copyright (C) 2016 CESNET
 *
 * LICENSE TERMS
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is'', and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <signal.h>
#include <getopt.h>
#include <inttypes.h>
#include <libtrap/trap.h>
#include <unirec/unirec.h>
#include "fields.h"
#include "lora_packet.h"
#include <string.h>
#include "black_list.h"

#define MAX_MSG_SIZE 10000

struct bl_device {
    uint64_t DEV_ADDR;
    double AIR_TIME;
    uint8_t ENABLE;
    uint64_t TIMESTAMP;
    struct bl_device *next;
};

/**
 * Definition of fields used in unirec templates (for both input and output interfaces) in this example basic flow from flow_meter
 */
/*This module functions as a filter of flows forwarded by flow_meter, I need all fields written below to be forwarded to the next module.*/
UR_FIELDS(
        string GW_ID,
        string NODE_MAC,
        uint64 TIMESTAMP,
        uint32 US_COUNT,
        uint32 FRQ,
        uint32 RF_CHAIN,
        uint32 RX_CHAIN,
        string STATUS,
        uint32 SIZE,
        string MOD,
        uint32 BAD_WIDTH,
        uint32 SF,
        uint32 CODE_RATE,
        double RSSI,
        double SNR,
        string APP_EUI,
        string APP_NONCE,
        string DEV_ADDR,
        string DEV_EUI,
        string DEV_NONCE,
        string FCNT,
        string FCTRL,
        string FHDR,
        string F_OPTS,
        string F_PORT,
        string FRM_PAYLOAD,
        string LORA_PACKET,
        string MAC_PAYLOAD,
        string MHDR,
        string MIC,
        string NET_ID,
        string PHY_PAYLOAD,
        uint64 AIR_TIME,
        uint8 ENABLE,
        string NWK_SKEY,
        string APP_SKEY
        )

trap_module_info_t *module_info = NULL;


/**
 * Definition of basic module information - module name, module description, number of input and output interfaces
 */
#define MODULE_BASIC_INFO(BASIC) \
  BASIC("Example detection module", \
        "This module serves as an example of module implementation in TRAP platform. It receives UniRec" \
        "with flow from different module (flowmeter). It is a filter, it resends all flows initiated on" \
        "d port and on an address.", 1, 1)
//BASIC(char *, char *, int, int)


/**
 * Definition of module parameters - every parameter has short_opt, long_opt, description,
 * flag whether an argument is required or it is optional and argument type which is NULL
 * in case the parameter does not need argument.
 * Module parameter argument types: int8, int16, int32, int64, uint8, uint16, uint32, uint64, float, string
 */
#define MODULE_PARAMS(PARAM) \
  PARAM('p', "port", "Port selected for for filtering.", required_argument, "uint16") \
  PARAM('d', "dutycycle", "Address selected for filtering.", required_argument, "double")
//PARAM(char, char *, char *, no_argument  or  required_argument, char *)
/**
 * To define positional parameter ("param" instead of "-m param" or "--mult param"), use the following definition:
 * PARAM('-', "", "Parameter description", required_argument, "string")
 * There can by any argument type mentioned few lines before.
 * This parameter will be listed in Additional parameters in module help output
 */


static int stop = 0;

/**
 * Function to handle SIGTERM and SIGINT signals (used to stop the module)
 */
TRAP_DEFAULT_SIGNAL_HANDLER(stop = 1)

int main(int argc, char **argv) {
    int ret;
    signed char opt;
    uint16_t port = 1;
    double dt = 0.1;

    /* **** TRAP initialization **** */

    /*
     * Macro allocates and initializes module_info structure according to MODULE_BASIC_INFO and MODULE_PARAMS
     * definitions on the lines 69 and 77 of this file. It also creates a string with short_opt letters for getopt
     * function called "module_getopt_string" and long_options field for getopt_long function in variable "long_options"
     */
    INIT_MODULE_INFO_STRUCT(MODULE_BASIC_INFO, MODULE_PARAMS)
    /*
     * Let TRAP library parse program arguments, extract its parameters and initialize module interfaces
     */
    TRAP_DEFAULT_INITIALIZATION(argc, argv, *module_info);

    /*
     * Register signal handler.
     */
    TRAP_REGISTER_DEFAULT_SIGNAL_HANDLER();

    /*
     * Parse program arguments defined by MODULE_PARAMS macro with getopt() function (getopt_long() if available)
     * This macro is defined in config.h file generated by configure script
     */
    while ((opt = TRAP_GETOPT(argc, argv, module_getopt_string, long_options)) != -1) {
        switch (opt) {
            case 'p':
                sscanf(optarg, "%" SCNu16, &port);
                break;
            case 'd':
                sscanf(optarg, "%lf", &dt);
                break;
            default:
                fprintf(stderr, "Invalid arguments.\n");
                FREE_MODULE_INFO_STRUCT(MODULE_BASIC_INFO, MODULE_PARAMS);
                TRAP_DEFAULT_FINALIZATION();
                return -1;
        }
    }



    /* **** Create UniRec templates **** */
    ur_template_t *in_tmplt = ur_create_input_template(0, "SIZE,SF,BAD_WIDTH,CODE_RATE,TIMESTAMP,PHY_PAYLOAD", NULL);
    if (in_tmplt == NULL) {
        fprintf(stderr, "Error: Input template could not be created.\n");
        return -1;
    }


    ur_template_t *out_tmplt = ur_create_output_template(0, "DEV_ADDR,TIMESTAMP,AIR_TIME,ENABLE,PHY_PAYLOAD", NULL);
    if (out_tmplt == NULL) {
        ur_free_template(in_tmplt);
        fprintf(stderr, "Error: Output template could not be created.\n");
        return -1;
    }

    // Allocate memory for output record
    void *out_rec = ur_create_record(out_tmplt, MAX_MSG_SIZE);
    if (out_rec == NULL) {
        ur_free_template(in_tmplt);
        ur_free_template(out_tmplt);
        fprintf(stderr, "Error: Memory allocation problem (output record).\n");
        return -1;
    }

    /* **** Main processing loop **** */
    // Read data from input, process them and write to output
    while (!stop) {
        const void *in_rec;
        uint16_t in_rec_size;

        // Receive data from input interface 0.
        // Block if data are not available immediately (unless a timeout is set using trap_ifcctl)
        ret = TRAP_RECEIVE(0, in_rec, in_rec_size, in_tmplt);

        // Handle possible errors
        TRAP_DEFAULT_RECV_ERROR_HANDLING(ret, continue, break);

        // Initialization LoRaWAN packet: 
        lr_initialization(ur_get_ptr(in_tmplt, in_rec, F_PHY_PAYLOAD));

        ur_set_string(out_tmplt, out_rec, F_MHDR, MHDR);
        ur_set_string(out_tmplt, out_rec, F_PHY_PAYLOAD, PHYPayload);

        if ((ur_get_len(in_tmplt, in_rec, F_NWK_SKEY) == 32) && (ur_get_len(in_tmplt, in_rec, F_APP_SKEY) == 32)) {
            ur_set_string(out_tmplt, out_rec, F_PHY_PAYLOAD, lr_uint8_to_string(lr_decode(
                    lr_arr_to_uint8(ur_get_var_as_str(in_tmplt, in_rec, F_NWK_SKEY)), 
                    lr_arr_to_uint8(ur_get_var_as_str(in_tmplt, in_rec, F_APP_SKEY)))));
        }

        if (lr_is_join_request_message()) {
            ur_set_string(out_tmplt, out_rec, F_APP_EUI, AppEUI);
            ur_set_string(out_tmplt, out_rec, F_DEV_EUI, DevEUI);
            ur_set_string(out_tmplt, out_rec, F_DEV_NONCE, DevNonce);
            ur_set_string(out_tmplt, out_rec, F_MIC, MIC);
        } else if (lr_is_join_accept_message()) {
            ur_set_string(out_tmplt, out_rec, F_APP_NONCE, AppNonce);
            ur_set_string(out_tmplt, out_rec, F_NET_ID, NetID);
            ur_set_string(out_tmplt, out_rec, F_DEV_ADDR, DevAddr);
            ur_set_string(out_tmplt, out_rec, F_MIC, MIC);
        } else if (lr_is_data_message()) {
            ur_set_string(out_tmplt, out_rec, F_DEV_ADDR, DevAddr);
            ur_set_string(out_tmplt, out_rec, F_FCTRL, FCtrl);
            ur_set_string(out_tmplt, out_rec, F_FCNT, FCnt);
            ur_set_string(out_tmplt, out_rec, F_MIC, MIC);
            ur_set_string(out_tmplt, out_rec, F_FHDR, FHDR);
            ur_set_string(out_tmplt, out_rec, F_F_PORT, FPort);
            ur_set_string(out_tmplt, out_rec, F_MAC_PAYLOAD, MACPayload);

            if (FOptsLen != 0)
                ur_set_string(out_tmplt, out_rec, F_F_OPTS, FOpts);
        }

        // Time between packet subsequent starts, duty cycle default value 0,10%
        // parm -d 0.1, 1, 10 ... [duty-cycle]
        double airtime = lr_airtime_calculate(ur_get(in_tmplt, in_rec, F_SIZE), ur_get(in_tmplt, in_rec, F_SF)
                , ur_get(in_tmplt, in_rec, F_CODE_RATE), 8, ur_get(in_tmplt, in_rec, F_BAD_WIDTH), dt);
        int timestamp = ur_get(in_tmplt, in_rec, F_TIMESTAMP);

        // Black List
        struct bl_device *pre = bl_get_device(lr_uint8_to_uint64(lr_arr_to_uint8(DevAddr)));

        if (pre != NULL) {
            if ((pre->TIMESTAMP + pre->AIR_TIME) <= timestamp)
                pre->ENABLE = 0;
            else
                pre->ENABLE = 1;
            pre->AIR_TIME = airtime;
            pre->TIMESTAMP = timestamp;

            if (((uint32_t) ur_get(in_tmplt, in_rec, F_SIZE) == ur_get_len(in_tmplt, in_rec, F_PHY_PAYLOAD)) && (ur_get_len(out_tmplt, out_rec, F_PHY_PAYLOAD) > 8)) {
                ur_set(out_tmplt, out_rec, F_ENABLE, pre->ENABLE);
                ur_set(out_tmplt, out_rec, F_AIR_TIME, pre->AIR_TIME);
                ur_set(out_tmplt, out_rec, F_TIMESTAMP, pre->TIMESTAMP);
                ur_copy_fields(out_tmplt, out_rec, out_tmplt, out_rec);

                ret = trap_send(0, out_rec, MAX_MSG_SIZE);
                TRAP_DEFAULT_SEND_ERROR_HANDLING(ret, continue, break);
            }
        } else {
            bl_insert_device(lr_uint8_to_uint64(lr_arr_to_uint8(DevAddr)), timestamp, airtime, 1);
        }

        lr_free();
    }


    /* **** Cleanup **** */

    // Do all necessary cleanup in libtrap before exiting
    TRAP_DEFAULT_FINALIZATION();

    // Release allocated memory for module_info structure
    FREE_MODULE_INFO_STRUCT(MODULE_BASIC_INFO, MODULE_PARAMS)

    // Free unirec templates and output record
    ur_free_record(out_rec);
    ur_free_template(in_tmplt);
    ur_free_template(out_tmplt);
    ur_finalize();


    return 0;
}
