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
        removeRequest(con->getFd());
    }
}

void HttpServer::onMessage(Connection *con, Buffer* buffer) {
    int fd = con->getFd();
    const void* crlf = buffer->findCRLF();
    Request* req = requestMap_[fd];
    while(crlf){
        const void* data = buffer->peek();
        string line(data, crlf - 1);
        if(!req->compelted()){
            size_t index = line.find(':');
            if(index == string::npos){
                LOG_ERROR("HttpServer::onMessage() Error request");
                removeRequest(con->getFd());
                server_.removeConnection(con);
                return;
            }
            string header = line.substr(0, index), content = line.substr(index + 1, line.size() - index - 1);
            req->setHeader(header, content);
        }
        else{
            req->clear();
            size_t index = line.find(' ');
            if(index == string::npos){
                removeRequest(con->getFd());
                LOG_ERROR("HttpServer::onMessage() Error request");
                server_.removeConnection(con);
                return;
            }
            string method = line.substr(0, index);
            size_t index2 = line.find(index + 1, ' ');
            if(index2 == string::npos){
                removeRequest(con->getFd());
                LOG_ERROR("HttpServer::onMessage() Error request");
                server_.removeConnection(con);
                return;
            }
            string path = line.substr(index + 1, index2 - index), version = line.substr(index2 + 1, line.size() - index2 - 1);
            req->setHeader("method", method);
            req->setHeader("path", path);
            req->setHeader("version", version);
            req->setIncompleted();
        }
        size_t len = crlf + 2 - data;
        buffer->retrieve(len);
        const void* tcrlf = buffer->findCRLF();
        if(tcrlf && tcrlf - crlf == 2){
            req->setCompleted();
            //handle requeset
        }
        crlf = tcrlf;
    }
}