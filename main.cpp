//
// Created by gxh on 2017/6/1.
//

#include "HttpServer.h"

using namespace simver;

int main(){
    EventLoop loop;
    HttpServer httpServer(80, &loop);
    httpServer.start();
    loop.loop();
}