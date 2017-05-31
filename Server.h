//
// Created by gxh on 2017/5/23.
//


#ifndef SIMVER_SERVER_H
#define SIMVER_SERVER_H

#include "Connection.h"

#include <stdint.h>
#include <unordered_map>
#include <string>


namespace simver{
    class Socket;
    class EventLoop;
    class Server{
    public:
        Server(std::string name, uint16_t port);
        ~Server();
        void onNewConnection(int con);
        void start();
        void removeConnection(Connection* con);
        void removeSocket(Socket* sock);
        void updateChannel(int op, Connection* con);

    private:
        std::string name_;
        EventLoop* loop_;
        Socket* socket_;
        std::unordered_map<std::string, Connection*> connectionMap_;
        ConnectionCallback connectionCallback_;
        MessageCallback messageCallback_;
        WriteCompleteCallback writeCompleteCallback_;
    };
}

#endif //SIMVER_SERVER_H