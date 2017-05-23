//
// Created by dell on 2017/5/19.
//

#ifndef SIMVER_CONNECTION_H
#define SIMVER_CONNECTION_H

#include "Channel.h"

namespace simver{
    class Connection : public Channel{
    public:
        Connection(int ev, int fd):Channel(ev, fd){}
        ~Connection();
        virtual void handleRead();

    };
}

#endif //SIMVER_CONNECTION_H
