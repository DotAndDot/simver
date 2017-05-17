#ifndef SIMVER_SOCKET_H
#define SIMVER_SOCKET_H

#include "Channel.h"
#include <netinet/in.h>

namespace simver{
    class Socket : public Channel{
    public:
        Socket(uint16_t port);
        ~Socket();
        void init();
        void onConnection();

    private:
        uint16_t port_;
        int family_;
        int sockfd_;
        struct sockaddr_in addr_;
    };
}

#endif
