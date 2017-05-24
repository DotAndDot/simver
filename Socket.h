#ifndef SIMVER_SOCKET_H
#define SIMVER_SOCKET_H

#include "Channel.h"
#include <netinet/in.h>
#include <functional>

namespace simver{
    class Socket : public Channel{
    public:
        typedef std::function<void (int)> ReadEventCallback;
        Socket(uint16_t port);
        ~Socket();
        void init();
        virtual void handleRead();
        void setReadCallback(const ReadEventCallback& cb){ readCallback_ = cb; }

    private:
        uint16_t port_;
        int family_;
        struct sockaddr_in addr_;
        ReadEventCallback readCallback_;
    };
}

#endif
