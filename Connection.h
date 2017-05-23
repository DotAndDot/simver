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

        typedef std::function<void (const Connection&)> ReadEventCallback;
        typedef std::function<void (const Connection&)> WriteCompleteCallback;


    private:
        std::string name_;
    };

    typedef std::shared_ptr<Connection> ConnectionPtr;
}



#endif //SIMVER_CONNECTION_H
