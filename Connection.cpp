//
// Created by dell on 2017/5/19.
//

#include "Connection.h"

using namespace simver;

Connection::Connection(std::string name, int fd)
    :Channel(0,fd),
    name_(name){
    setReadEvents();
}

void Connection::handleRead(){

}

void Connection::handleClose() {
    closeCallback_(this);
}
