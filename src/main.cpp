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

    // begin polling
    printf("Beginning polling\n");
    controller *cntrl = 0;
    while (1)
    {
        // if 0, wasnt updated recently
        //      otherwise, update!!
        cntrl = update_controller();
        if (cntrl)
        {
            write_to_ps2(cntrl);
        }
    }
}
