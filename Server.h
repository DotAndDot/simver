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
        Server(std::string name, uint16_t port, EventLoop* evloop);
        ~Server();
        void onNewConnection(int con);
        void start();
        void removeConnection(Connection* con);
        void removeSocket(Socket* sock);
        void updateChannel(int op, Connection* con);
        void setConnectionCallback(const ConnectionCallback& cb){ connectionCallback_ = cb; }
        void setMessageCallback(const MessageCallback& cb){ messageCallback_ = cb; }
        void setWriteCompleteCallback(const WriteCompleteCallback& cb){ writeCompleteCallback_ = cb; }

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