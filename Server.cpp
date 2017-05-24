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

Server::~Server() {
    removeSocket(socket_);
    delete socket_;
    for(auto &it : connectionMap_){
        removeConnection(it.second);
    }
}

void Server::start() {
    loop_->addChannel(socket_);
    socket_->init();
}

void Server::onNewConnection(int con) {
    string name(name_ + to_string(con));
    Connection* connection = new Connection(name, con);
    connectionMap_[name] = connection;
    connection->setConnectionCallback(connectionCallback_);
    connection->setMessageCallback(messageCallback_);
    connection->setWriteCompleteCallback(writeCompleteCallback_);
    connection->setCloseCallback(bind(&Server::removeConnection, this, _1));
    loop_->addChannel(connection);
    connectionCallback_(connection);
}

void Server::removeConnection(Connection *con) {
    loop_->removeChannel(con);
    string name = con->getName();
    delete connectionMap_[name];
    connectionMap_.erase(name);
}

void Server::removeSocket(Socket* sock){
    loop_->removeChannel(sock);
}