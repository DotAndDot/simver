//
// Created by gxh on 2017/6/1.
//

#ifndef SIMVER_HTTPSERVER_H
#define SIMVER_HTTPSERVER_H

#include "Server.h"
#include "EventLoop.h"
#include <unordered_map>
#include "Request.h"

class HttpServer{
public:
    HttpServer(uint16_t port, simver::EventLoop* loop);
    ~HttpServer();
    void start();
    void onConnection(simver::Connection* con);
    void onMessage(simver::Connection* con, simver::Buffer* buffer);

private:
    simver::Server server_;
    std::unordered_map<int, Request*> requestMap_;
};

#endif //SIMVER_HTTPSERVER_H
