#ifndef __BLE_HANDLER_H_
#define __BLE_HANDLER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.hpp"
#include "simpleble_c/simpleble.h"

// UUID defines
#define ADAPTER_SERVICE_UUID "3784ee57-bda7-499b-a1a6-146e063a62e3"
#define ADAPTER_CHARACTERISTIC_UUID "680f8715-b97a-4ff5-bb0c-4ca4f37d9b94"
#define BLE_ADDRESS "f4:12:fa:65:5b:dd"

    typedef struct
    {
        simpleble_uuid_t service;
        simpleble_uuid_t characteristic;
    } service_characteristic_t;

    /**
     * @brief at start of program initializes a connection with the BLE
     *      device the program will connect to. If it fails, the program ends
     * @returns 0 on success, 1 on failure
     */
    uint8_t initialize_ble();

    /**
     * @brief writes a given controller scheme to the ps2
     * @param [in] cntrl a pointer to the controller struct to send over
     */
    void write_to_ps2(controller *cntrl);

#ifdef __cplusplus
}
#endif

#endif
