#include <stdio.h>

#include "main.hpp"
#include "ble_handler.hpp"
#include "client.hpp"
#include "wiimote_handle.h"

int main()
{
    // start ble, exit if failed
    printf("Initializing BLE\n");
    if (initialize_ble())
        return 0;
    printf("Initializing wiimote\n");
    if (init_wiimote_handler())
        return 0;
    printf("Initializing SocketIO\n");
    init_socketio();
}
