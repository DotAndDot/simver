#include "Socket.h"
#include "log/log.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>

using namespace simver;

Socket::Socket(uint16_t port)
    : Channel(0, 0),
      port_(port),
      family_(AF_INET)
    {
        channelfd_ = socket(family_, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        if(channelfd_ < 0){
            LOG_ERROR("Socket::Socket(int port) : create socket fail");
        }
        addr_.sin_family = family_;
        addr_.sin_addr.s_addr = INADDR_ANY;
        addr_.sin_port = htons(port_);

        setReadEvents();
    }

void Socket::init(){
    int res = bind(channelfd_, (struct sockaddr*)&addr_, sizeof(addr_));
    if(res < 0){
        LOG_ERROR("Socket::bind() : bind fail");
    }

    res = listen(channelfd_, SOMAXCONN);
    if(res < 0){
        LOG_ERROR("Socket::listen() : listen fail");
    }
}

void Socket::handleRead() {
    struct sockaddr add;
    bzero(&add, sizeof(add));
    int con = accept(channelfd_, &add, sizeof(add));
    readCallback_(con);
}


