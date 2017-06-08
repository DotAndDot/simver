//
// Created by gxh on 2017/6/1.
//
#include "HttpServer.h"

using namespace simver;
using namespace std;
using namespace std::placeholders;

HttpServer::HttpServer(uint16_t port, simver::EventLoop *loop)
        :server_("simver", port, loop){
    server_.setConnectionCallback(bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(bind(&HttpServer::onMessage, this, _1));
}

void HttpServer::start() {
    server_.start();
}

void HttpServer::onConnection(Connection *con) {
    if(con->connected()){
        requestMap_[con->getFd()] = new Request();
    }
    else{
        requestMap_.erase(con->getFd());
    }
}

void HttpServer::onMessage(Connection *con) {

}