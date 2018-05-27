/* 
 * File:   black_list.c
 * Author: Erik Gresak
 * Email: gre0071@vsb.cz
 * Created on March 21, 2018, 9:12 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "black_list.h"

struct bl_device {
    uint64_t DEV_ADDR;
    double AIR_TIME;
    uint8_t ENABLE;
    uint64_t TIMESTAMP;
    struct bl_device *next;
};

struct bl_device *head = NULL;
struct bl_device *current = NULL;

void bl_insert_device(uint64_t dev_addr, uint64_t timestamp, double air_time, uint8_t enable) {

    struct bl_device *add = (struct bl_device*) malloc(sizeof (struct bl_device));

    add->DEV_ADDR = dev_addr;
    add->AIR_TIME = air_time;
    add->TIMESTAMP = timestamp;
    add->ENABLE = enable;
    add->next = head;
    head = add;
}

uint8_t bl_is_empty() {
    head = NULL;
    return 0;
}

uint8_t bl_is_exist(uint64_t dev_addr) {
    if (bl_get_device(dev_addr) != NULL)
        return 1;
    return 0;
}

struct bl_device* bl_get_device(uint64_t dev_addr) {

    struct bl_device* current = head;

    if (head == NULL)
        return NULL;

    while (current->DEV_ADDR != dev_addr) {
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;
    }

    return current;
}