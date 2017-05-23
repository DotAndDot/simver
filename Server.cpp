//
// Created by gxh on 2017/5/23.
//

#include "Server.h"
#include "Channel.h"
#include "Socket.h"
#include "EventLoop.h"

using namespace std;
using namespace simver;
using namespace std::placeholders;

Server::Server(string name, uint16_t port)
        : name_(name),
          socket_(new Socket(port)){
    socket_->setReadCallback(std::bind(&Server::onNewConnection, this, _1));
}

void Server::start() {
    loop_->addChannel(socket_);
    socket_->init();
}

void Server::onNewConnection(int con) {
    string name(name_ + to_string(con));
    ConnectionPtr connection(new Connection(name, con));
    connectionMap_[name] = connection;

}