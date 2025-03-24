#ifndef __CLIENT_H_
#define __CLIENT_H_

#include "main.hpp"

/**
 * @returns 0 if controlelr wasn't updated, pointer if it was
 */
controller *update_controller();

/**
 * initializes the client to connect to server
 */
void init_socketio();

#endif
