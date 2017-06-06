//
// Created by gxh on 2017/6/1.
//

#ifndef SIMVER_HTTPSERVER_H
#define SIMVER_HTTPSERVER_H

#include "Server.h"
#include "EventLoop.h"

class Connection;
class HttpServer{
public:
    HttpServer(uint16_t port, simver::EventLoop* loop);
    ~HttpServer();
    void start();
    void onConnection(Connection* con);
    void onMessage(Connection* con);

    simver::Server server_;

};

#endif //SIMVER_HTTPSERVER_H
