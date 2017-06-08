//
// Created by dell on 2017/5/19.
//

#ifndef SIMVER_CONNECTION_H
#define SIMVER_CONNECTION_H

#include "Channel.h"
#include "Buffer.h"
#include <string>
#include <memory>
#include <functional>

namespace simver{
    class Buffer;
    class Connection;
    typedef std::function<void (Connection*)> ConnectionCallback;
    typedef std::function<void (Connection*)> WriteCompleteCallback;
    typedef std::function<void (Connection*, Buffer*)> MessageCallback;
    typedef std::function<void (Connection*)> CloseCallback;
    class Connection : public Channel{
    public:
        Connection(std::string name, int fd);
        ~Connection();
        void setState(std::string sta){ state_ = sta; }
        bool connected(){ return state_ == "connected"; }

        virtual void handleRead();
        virtual void handleWrite();
        virtual void handleClose();
        virtual void handleError();

        void setConnectionCallback(const ConnectionCallback& cb){ connectionCallback_ = cb; }
        void setWriteCompleteCallback(const WriteCompleteCallback& cb){ writeCompleteCallback_ = cb; }
        void setMessageCallback(const MessageCallback& cb){ messageCallback_ = cb; }
        void setCloseCallback(const CloseCallback& cb){ closeCallback_ = cb; }

        typedef std::function<void (int, Connection*)> UpdateFunc;
        void setUpdateFunc(const UpdateFunc& func){ updateConnection_ = func; }

        void send(Buffer* buf);

        std::string getName(){ return name_; }

    private:
        std::string name_;
        std::string state_;
        ConnectionCallback connectionCallback_;
        WriteCompleteCallback writeCompleteCallback_;
        MessageCallback messageCallback_;
        CloseCallback closeCallback_;

        UpdateFunc updateConnection_;

        Buffer inputBuffer_;
        Buffer outputBuffer_;
    };


}



#endif //SIMVER_CONNECTION_H
