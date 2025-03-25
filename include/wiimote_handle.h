#ifndef __WIIMOTE_HANDLE_H_
#define __WIIMOTE_HANDLE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/********************** 1 MEANS RELEASED/0 MEANS PRESSED **********************/
/**
 * BUTTOM MAP 1
 */
#define BM1_SELECT_MASK (1 << 0)
#define BM1_L3_MASK (1 << 1)
#define BM1_R3_MASK (1 << 2)
#define BM1_START_MASK (1 << 3)
#define BM1_UP_MASK (1 << 4)
#define BM1_RIGHT_MASK (1 << 5)
#define BM1_DOWN_MASK (1 << 6)
#define BM1_LEFT_MASK (1 << 7)

/**
 * BUTTOM MAP 2
 */
#define BM2_L2_MASK (1 << 0)
#define BM2_R2_MASK (1 << 1)
#define BM2_L1_MASK (1 << 2)
#define BM2_R1_MASK (1 << 3)
#define BM2_TRIANGLE_MASK (1 << 4)
#define BM2_O_MASK (1 << 5)
#define BM2_X_MASK (1 << 6)
#define BM2_SQUARE_MASK (1 << 7)

    /**
     * @brief looks for nearby wiimotes to connect to. loops until one is found.
     * @returns 0 on success, 1 on failure
     */
    uint8_t init_wiimote_handler();

    /**
     * @brief begins an infinite loop of polling for wiimote state, and connects to
     *      the ble handler to write new states of the wiimote to it
     */
    void begin_polling();

#ifdef __cplusplus
}
#endif

#endif
