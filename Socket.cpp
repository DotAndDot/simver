#include "Socket.h"
#include "log/log.h"
#include <sys/types.h>
#include <sys/socket.h>

using namespace simver;

Socket::Socket(uint16_t port)
    : port_(port),
      family_(AF_INET)
    {
        sockfd_ = socket(family_, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        if(sockfd_ < 0){
            LOG_ERROR("Socket::Socket(int port) : create socket fail");
        }
        addr_.sin_family = family_;
        addr_.sin_addr.s_addr = INADDR_ANY;
        addr_.sin_port = htons(port_);
    }

void Socket::init(){
    int res = bind(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_));
    if(res < 0){
        LOG_ERROR("Socket::bind() : bind fail");
    }

    res = listen(sockfd_, SOMAXCONN);
    if(res < 0){
        LOG_ERROR("Socket::listen() : listen fail");
    }
}


