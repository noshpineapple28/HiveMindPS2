#ifndef __CONNECTION_LISTENER_HPP_
#define __CONNECTION_LISTENER_HPP_

#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <thread>

#include "../lib/socket.io-client-cpp/src/sio_client.h"

class connection_listener
{
    sio::client &handler;

public:
    std::mutex lock;
    std::condition_variable_any cond;
    bool connect_finish = false;

    connection_listener(sio::client &h);
    void on_connected();
    void on_close(sio::client::close_reason const &reason);
    void on_fail();
};

#endif
