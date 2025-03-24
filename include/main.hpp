#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>

typedef struct controller {
    uint8_t l_dx;
    uint8_t l_dy;
    uint8_t r_dx;
    uint8_t r_dy;
    uint8_t button_map_1;
    uint8_t button_map_2;
} controller;

#endif
