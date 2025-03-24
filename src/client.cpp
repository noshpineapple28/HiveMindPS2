#include <stdio.h>

#include "../lib/socket.io-client-cpp/src/sio_client.h"
#include "connection_listener.hpp"

#include "client.hpp"

sio::socket::ptr current_socket;
uint8_t was_updated = 0;
controller cntrl = {0};

/**
 * @returns 0 if controlelr wasn't updated, pointer if it was
 */
controller *update_controller()
{
    if (was_updated)
    {
        was_updated = 0;
        return &cntrl;
    }

    return 0;
}

/**
 * initializes the client to connect to server
 */
void init_socketio()
{
    sio::client h;
    connection_listener l(h);

    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l, std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
    h.connect("http://localhost:3000/");

    l.lock.lock();
    if (!l.connect_finish)
    {
        l.cond.wait(l.lock);
    }
    l.lock.unlock();
    current_socket = h.socket();

    current_socket->on("update controller",
                       sio::socket::event_listener_aux([&](
                                                           std::string const &name,
                                                           sio::message::ptr const &data,
                                                           bool isAck,
                                                           sio::message::list &ack_resp)
                                                       {
                                                            l.lock.lock();
                                                            cntrl.button_map_1 = data->get_map()["BM1"]->get_int();
                                                            cntrl.button_map_2 = data->get_map()["BM2"]->get_int();
                                                            cntrl.r_dx = data->get_map()["RX"]->get_int();
                                                            cntrl.r_dy = data->get_map()["RY"]->get_int();
                                                            cntrl.l_dx = data->get_map()["LX"]->get_int();
                                                            cntrl.l_dy = data->get_map()["LY"]->get_int();
                                                            // send state of the controller to ps2
                                                            was_updated = 1;
                                                            l.lock.unlock(); }));
    h.sync_close();
    h.clear_con_listeners();
}
