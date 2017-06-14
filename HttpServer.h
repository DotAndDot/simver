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
    void handleRequest(Request* request, simver::Connection* con);
    void notFound(simver::Connection* con);
    void badRequest(simver::Connection* con);
    void serverFile(simver::Connection* con, std::string path);

    void removeRequest(int in){
        if(requestMap_.find(in) != requestMap_.end()){
            delete requestMap_[in];
            requestMap_.erase(in);
        }
    }

private:
    simver::Server server_;
    std::unordered_map<int, Request*> requestMap_;
    static std::string WWW_PATH;
};

#endif //SIMVER_HTTPSERVER_H
