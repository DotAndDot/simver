//
// Created by dell on 2017/5/19.
//

#ifndef SIMVER_CONNECTION_H
#define SIMVER_CONNECTION_H

#include "Channel.h"

#include <string>
#include <memory>
#include <functional>

namespace simver{
    class Connection : public Channel{
    public:
        Connection(std::string name, int fd);
        ~Connection();
        virtual void handleRead();
        virtual void handleWrite();
        virtual void handleClose();

        typedef std::function<void (Connection*)> ConnectionCallback;
        typedef std::function<void (Connection*)> WriteCompleteCallback;
        typedef std::function<void (Connection*)> MessageCallback;
        typedef std::function<void (Connection*)> CloseCallback;
        void setConnectionCallback(const ConnectionCallback& cb){ connectionCallback_ = cb; }
        void setWriteCompleteCallback(const WriteCompleteCallback& cb){ writeCompleteCallback_ = cb; }
        void setMessageCallback(const MessageCallback& cb){ messageCallback_ = cb; }
        void setCloseCallback(const CloseCallback& cb){ closeCallback_ = cb; }

        std::string getName(){ return name_; }

    private:
        std::string name_;
        ConnectionCallback connectionCallback_;
        WriteCompleteCallback writeCompleteCallback_;
        MessageCallback messageCallback_;
        CloseCallback closeCallback_;
    };


}



#endif //SIMVER_CONNECTION_H
