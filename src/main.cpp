#include <stdio.h>

#include "main.hpp"
#include "ble_handler.hpp"
#include "client.hpp"

int main()
{
    // start ble, exit if failed
    printf("Initializing BLE\n");
    if (initialize_ble())
        return 0;
    printf("Initializing SocketIO\n");
    init_socketio();
}
