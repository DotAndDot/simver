//
// Created by gxh on 2017/6/1.
//
#include "HttpServer.h"

using namespace simver;

HttpServer::HttpServer(uint16_t port, simver::EventLoop *loop)
        :server_("simver", port, loop){}

void HttpServer::start() {
    server_.start();
}