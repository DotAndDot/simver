//
// Created by gxh on 2017/6/1.
//
#include "HttpServer.h"
#include "log/log.h"

using namespace simver;
using namespace std;
using namespace std::placeholders;

HttpServer::HttpServer(uint16_t port, simver::EventLoop *loop)
        :server_("simver", port, loop){
    server_.setConnectionCallback(bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(bind(&HttpServer::onMessage, this, _1, _2));
}

void HttpServer::start() {
    server_.start();
}

void HttpServer::onConnection(Connection *con) {
    if(con->connected()){
        requestMap_[con->getFd()] = new Request();
    }
    else{
        delete requestMap_[con->getFd()];
        requestMap_.erase(con->getFd());
    }
}

void HttpServer::onMessage(Connection *con, Buffer* buffer) {
    int fd = con->getFd();
    const void* crlf = buffer->findCRLF();
    Request* req = requestMap_[fd];
    while(crlf){
        const void* data = buffer->peek();
        if(!req->compelted()){
            string line(data, crlf - 1);
            size_t index = line.find(':');
            if(index == string::npos){
                LOG_ERROR("HttpServer::onMessage() Error request");
                return;
            }
            string header = line.substr(0, index), content = line.substr(index + 1, line.size() - index);
            req->setHeader(header, content);
        }
        else{
            req->clear();

        }
    }
}