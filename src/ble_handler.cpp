#include "ble_handler.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

simpleble_peripheral_t ps2_peripheral = NULL;
static simpleble_adapter_t adapter = NULL;
static service_characteristic_t characteristic = {0};

/**
 * disconnects the ps2 peripheral
 */
void disconnect_ps2()
{
    simpleble_peripheral_disconnect(ps2_peripheral);
}

/**
 * on program exit, cleares used resources
 */
static void clean_on_exit(void)
{
    printf("Releasing allocated resources.\n");

    if (ps2_peripheral)
        disconnect_ps2();

    // Release all saved peripherals
    simpleble_peripheral_release_handle(ps2_peripheral);

    // Let's not forget to release the associated handle.
    simpleble_adapter_release_handle(adapter);
}

/**
 * callback for when the adapter begins scanning
 */
static void adapter_on_scan_start(simpleble_adapter_t adapter, void *userdata)
{
    char *identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL)
    {
        return;
    }

    printf("Adapter %s started scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

/**
 * whenever the scanning ends, this runs
 */
static void adapter_on_scan_stop(simpleble_adapter_t adapter, void *userdata)
{
    char *identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL)
    {
        return;
    }

    printf("Adapter %s stopped scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

/**
 * @brief on finding a device, this will connect. If a puppet is found, the program
 *      ends scanning
 */
static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void *userdata)
{
    char *adapter_identifier = simpleble_adapter_identifier(adapter);
    char *peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char *peripheral_address = simpleble_peripheral_address(peripheral);

    if (adapter_identifier == NULL || peripheral_identifier == NULL || peripheral_address == NULL)
    {
        return;
    }

    if (!strcmp(peripheral_address, BLE_ADDRESS))
    {
        printf("Found %s found device: %s [%s]\n", adapter_identifier, peripheral_identifier, peripheral_address);
        ps2_peripheral = peripheral;
        // stop scanning
        simpleble_adapter_scan_stop(adapter);
    }
    else
    {
        // As there was no space left for this peripheral, release the associated handle.
        simpleble_peripheral_release_handle(peripheral);
    }

    // Let's not forget to release all allocated memory.
    simpleble_free(peripheral_identifier);
    simpleble_free(peripheral_address);
}

uint8_t initialize_ble()
{
    simpleble_err_t err_code = SIMPLEBLE_SUCCESS;
    atexit(clean_on_exit);

    // load driver
    size_t adapter_count = simpleble_adapter_get_count();
    if (adapter_count == 0)
    {
        printf("No adapter was found.\n");
        return 1;
    }
    adapter = simpleble_adapter_get_handle(0);
    if (adapter == NULL)
    {
        printf("No adapter was found.\n");
        return 1;
    }
    // setup adapter
    simpleble_adapter_set_callback_on_scan_start(adapter, adapter_on_scan_start, NULL);
    simpleble_adapter_set_callback_on_scan_stop(adapter, adapter_on_scan_stop, NULL);
    simpleble_adapter_set_callback_on_scan_found(adapter, adapter_on_scan_found, NULL);
    // scan
    simpleble_adapter_scan_for(adapter, 10000);

    // connect to peripheral
    err_code = simpleble_peripheral_connect(ps2_peripheral);
    if (err_code != SIMPLEBLE_SUCCESS)
    {
        printf("Failed to connect.\n");
        return 1;
    }

    // get the service and characteristic
    uint8_t characteristic_count = 0;
    simpleble_service_t service;
    err_code = simpleble_peripheral_services_get(ps2_peripheral, 2, &service);

    if (err_code != SIMPLEBLE_SUCCESS)
    {
        printf("Failed to get service.\n");
        return 1;
    }
    characteristic.service = service.uuid;
    characteristic.characteristic = service.characteristics[0].uuid;

    return 0;
}

void write_to_ps2(controller *cntrl)
{
    static uint32_t count = 0;
    simpleble_err_t err = simpleble_peripheral_write_command(
        ps2_peripheral,
        characteristic.service,
        characteristic.characteristic,
        (uint8_t *)cntrl,
        6);
    if (err)
        printf("\nFAILED TO WRITE DATA TO PS2\n");
    else
        printf("Successfully wrote to wiimote %d\r", ++count);
}
