#include <iostream>
#include "connection_listener.hpp"

connection_listener::connection_listener(sio::client &h) : handler(h)
{
}

void connection_listener::on_connected()
{
    this->lock.lock();
    this->cond.notify_all();
    this->connect_finish = true;
    this->lock.unlock();
}
void connection_listener::on_close(sio::client::close_reason const &reason)
{
    std::cout << "sio closed " << std::endl;
    exit(0);
}

void connection_listener::on_fail()
{
    std::cout << "sio failed " << std::endl;
    exit(0);
}
