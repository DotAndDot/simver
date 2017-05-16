#ifndef SIMVER_SOCKET_H
#define SIMVER_SOCKET_H

#include "Channel.h"

namespace simver{
    class Socket : public Channel{
    public:
        Socket(int port);
        ~Socket();

    }
}

#endif
