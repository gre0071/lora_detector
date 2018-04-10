/* 
 * File:   lora_packet.c
 * Author: Erik Gresak
 * Email: gre0071@vsb.cz
 * Created on March 21, 2018, 9:12 AM
 */




#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "lora_packet.h"
//#include "aes/aes.h"

// Sector Constant
#define MTYPE_JOIN_REQUEST 0
#define MTYPE_JOIN_ACCEPT 1
#define MTYPE_UNCONFIRMED_DATA_UP 2
#define MTYPE_UNCONFIRMED_DATA_DOWN 3
#define MTYPE_CONFIRMED_DATA_UP 4
#define MTYPE_CONFIRMED_DATA_DOWN 5

#define MTYPE_DIRECTIONS_UP 0x00
#define MTYPE_DIRECTIONS_DOWN 0x01
// endSector

char *lr_slice(char *arr, size_t start, size_t size) {
    if (arr == NULL)
        return NULL;

    char *_arr = (char*) malloc(size + 1);

    int i;
    for (i = start; i < size + start; i++) {
        _arr[i - start] = arr[i];
    }

    _arr[size] = '\0';

    return _arr;
}

char *lr_revers_array(char *arr) {
    if (arr == NULL)
        return NULL;

    int end = strlen(arr);
    int len = strlen(arr);

    char *_array = (char*) malloc(len + 1);

    int i;
    for (i = 0; i < len; i++) {
        --end;
        if ((i % 2) == 0) {
            _array[i] = arr[end - 1];
        } else {
            _array[i] = arr[end + 1];
        }
    }

    _array[len] = '\0';

    return _array;
}

uint8_t *lr_arr_to_uint8(char* arr) {
    if (arr == NULL)
        return NULL;

    int len = strlen(arr);
    uint8_t *_array = (uint8_t*) malloc(len);

    char tk[] = {'0', '0', '\0'};
    unsigned int i, a, ple;
    for (i = 0, a = 0, ple = 0; i < len; i++) {
        if ((i % 2) == 0) {
            tk[0] = arr[i];
            tk[1] = arr[i + 1];
            ple = lr_get_int(tk);
            _array[a] = (uint8_t) (ple);
            a++;
        }
    }

    _array[len] = '\0';

    return _array;
}

uint64_t lr_uint8_to_uint64(uint8_t* var) {
    return (((uint64_t) var[7]) << 56) |
            (((uint64_t) var[6]) << 48) |
            (((uint64_t) var[5]) << 40) |
            (((uint64_t) var[4]) << 32) |
            (((uint64_t) var[3]) << 24) |
            (((uint64_t) var[2]) << 16) |
            (((uint64_t) var[1]) << 8) |
            (((uint64_t) var[0]) << 0);
}

static void lr_print_uint8(uint8_t* str) {
    unsigned int len = (strlen(str));
    unsigned char i;
    for (i = 0; i < len; ++i) {
        printf("%.2x", str[i]);
    }
    printf("\n");
}

int lr_get_int(char *arr) {
    char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *_i = (char*) malloc(strlen(arr));
    int len = strlen(arr);
    int j, decimal = 0;

    int i;
    for (i = 0; i < len; i++) {
        _i[i] = arr[i];
    }

    for (i = 0; i < len; i++) {
        for (j = 0; j < 16; j++) {
            if (_i[i] == hexDigits[j]) {
                decimal += j * (int) pow(16, (len - 1) - i);
            }
        }
    }

    free(_i);
    _i = NULL;

    return decimal;
}

int lr_get_message_type() {
    return (lr_get_int(MHDR) & 0xff) >> 5; //5
}

uint8_t lr_get_direction() {
    switch (lr_get_message_type()) {
        case MTYPE_JOIN_REQUEST:
            return MTYPE_DIRECTIONS_UP;
        case MTYPE_JOIN_ACCEPT:
            return MTYPE_DIRECTIONS_DOWN;
        case MTYPE_UNCONFIRMED_DATA_UP:
            return MTYPE_DIRECTIONS_UP;
        case MTYPE_UNCONFIRMED_DATA_DOWN:
            return MTYPE_DIRECTIONS_DOWN;
        case MTYPE_CONFIRMED_DATA_UP:
            return MTYPE_DIRECTIONS_UP;
        case MTYPE_CONFIRMED_DATA_DOWN:
            return MTYPE_DIRECTIONS_DOWN;
        default:
            return 0x00; // TODO Error
    }
}

bool lr_is_data_message() {
    switch (lr_get_message_type()) {
        case MTYPE_UNCONFIRMED_DATA_UP:
        case MTYPE_UNCONFIRMED_DATA_DOWN:
        case MTYPE_CONFIRMED_DATA_UP:
        case MTYPE_CONFIRMED_DATA_DOWN:
            return true;
        default:
            return false;
    }
}

bool lr_is_join_request_message() {
    return (lr_get_message_type() == MTYPE_JOIN_REQUEST);
}

bool lr_is_join_accept_message() {
    return (lr_get_message_type() == MTYPE_JOIN_ACCEPT);
}

void lr_free() {
    free(MHDR);
    free(FCtrl);
    free(FCnt);
    free(FRMPayload);
    free(FPort);
    free(AppEUI);
    free(DevEUI);
    free(DevNonce);
    free(MIC);
    free(AppNonce);
    free(NetID);
    free(CFList);
    free(MACPayload);
    free(FOpts);
    free(FHDR);

    MHDR = NULL;
    FCtrl = NULL;
    FCnt = NULL;
    FRMPayload = NULL;
    FPort = NULL;
    AppEUI = NULL;
    DevEUI = NULL;
    DevNonce = NULL;
    MIC = NULL;
    AppNonce = NULL;
    NetID = NULL;
    CFList = NULL;
    MACPayload = NULL;
    FOpts = NULL;
    FHDR = NULL;
}

// Sector initialization

void lr_initialization(char* packet) {
    size_t _strl = strlen(packet);
    char *_packet = packet;

    // initialization
    MHDR = (char*) malloc(2);
    MIC = (char*) malloc(8);
    FCtrl = (char*) malloc(2);
    DevAddr = (char*) malloc(8);
    FCnt = (char*) malloc(4);
    FRMPayload = (char*) malloc(0);
    FPort = (char*) malloc(0);

    AppEUI = (char*) malloc(16);
    DevEUI = (char*) malloc(16);
    DevNonce = (char*) malloc(4);
    MIC = (char*) malloc(8);

    AppNonce = (char*) malloc(6);
    NetID = (char*) malloc(6);
    DevAddr = (char*) malloc(8);
    CFList = (char*) malloc(0);

    PHYPayload = packet;
    MHDR = lr_slice(_packet, 0, 2);

    if (lr_is_join_request_message()) {
        AppEUI = lr_revers_array(lr_slice(_packet, 2, 16));
        DevEUI = lr_revers_array(lr_slice(_packet, 18, 16));
        DevNonce = lr_revers_array(lr_slice(_packet, 34, 4));
        MIC = lr_slice(_packet, _strl - 8, 8);
    } else if (lr_is_join_accept_message()) {
        AppNonce = lr_revers_array(lr_slice(_packet, 2, 6));
        NetID = lr_revers_array(lr_slice(_packet, 8, 6));
        DevAddr = lr_revers_array(lr_slice(_packet, 14, 8));
        DLSettings = lr_get_int(_packet);
        RxDelay = lr_get_int(_packet);
        if (_strl == 66) {
            CFList = (char*) malloc(32);
            CFList = lr_slice(_packet, 26, 32);
        }
        MIC = lr_slice(_packet, _strl - 8, 8);
    } else if (lr_is_data_message()) {


        MACPayload = (char*) malloc(_strl - 10);

        MACPayload = lr_slice(_packet, 2, (_strl - 10));
        MIC = lr_slice(_packet, (_strl - 8), 8);

        FCtrl = lr_slice(MACPayload, 8, 2);

        int _FCtrl = lr_get_int(FCtrl);
        int FOptsLen = (_FCtrl & 0x0f) *2;

        if (FOptsLen != 0) {
            FOpts = (char*) malloc(FOptsLen);
            FOpts = lr_slice(MACPayload, 14, FOptsLen);
        }



        int FHDR_length = 14 + FOptsLen;
        FHDR = (char*) malloc(FHDR_length);
        FHDR = lr_slice(MACPayload, 0, 0 + FHDR_length);
        DevAddr = lr_revers_array(lr_slice(FHDR, 0, 8));

        FCnt = lr_slice(FHDR, 10, 4);
        FCnt = lr_revers_array(FCnt);

        if (FHDR_length != strlen(MACPayload)) {
            FPort = (char*) malloc(2);
            FPort = lr_slice(MACPayload, FHDR_length, 2);

            if (FHDR_length < strlen(MACPayload)) {
                FRMPayload = (char*) malloc(strlen(MACPayload)-(FHDR_length + 2));
                FRMPayload = lr_slice(MACPayload, FHDR_length + 2, strlen(MACPayload) - (FHDR_length + 2));
            }
        }

    }

}
// endSector

// Sector lora packet decode
// TODO

uint8_t *lr_decode(uint8_t* nwkSKey, uint8_t* appSKey) {

    int block = 0, len = 0;
    len = (strlen(FRMPayload) / 2);
    block = ceil(len / 16.0);

    uint8_t *payload = lr_arr_to_uint8(FRMPayload);
    uint8_t *devAddr = lr_arr_to_uint8(DevAddr);
    uint8_t *S = (uint8_t*) malloc(16 * block);
    uint8_t *Si = (uint8_t*) malloc(16);
    uint8_t *dec = (uint8_t*) malloc(16 * block);

    int i;
    for (i = 0; i < block; i++) {

        // construct A blocks (Ai)
        uint8_t ai_buf[] = {// plain_s
            0x01, // Def
            0x00,
            0x00,
            0x00,
            0x00,
            lr_get_direction(), // Direction up/down
            devAddr[3], // DevAddr
            devAddr[2],
            devAddr[1],
            devAddr[0],
            0x00, // FCnt BigEndian
            0x00,
            0x00, // upper 2 bytes of FCnt (zeroes)
            0x00,
            0x00, // 0x00
            (uint8_t) (i + 1) // Block number +1     
        };

        // TODO
        //        AES_ECB_encrypt(ai_buf, appSKey, Si, 16);

        memcpy(S + (16 * i), Si, 16);

    }

    for (i = 0; i < len; i++) {
        dec[i] = (payload[i] | 0x00) ^ S[i];
    }

    return dec;
}
// endSector

// Sector air-time calculate

double lr_airtime_calculate(uint32_t pay_size, uint32_t sf, uint32_t cd_rate, uint32_t prem_sym, uint32_t band) {
    double t_sym, t_premble, pay_symb_nb, t_payload, t_packet, symb = 0.0;

    t_sym = pow(2.0, sf) / (band * 1000.0) * 1000.0;
    t_premble = (prem_sym + 4.25) * t_sym;
    symb = (ceil((8.0 * pay_size - 4.0 * sf + 28 + 16 - 20.0 * (1 - 1)) / (4.0 * (sf - 2.0 * 0)))*(cd_rate));
    pay_symb_nb = 8 + (symb < 0 ? 0 : symb);
    t_payload = pay_symb_nb * t_sym;
    t_packet = t_premble + t_payload;

    return t_packet * 1000;
}
// endSector