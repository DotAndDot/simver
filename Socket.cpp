#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <errno.h>
#include "Socket.h"
#include "log/log.h"

using namespace simver;

Socket::Socket(uint16_t port)
    : Channel(0, 0),
      port_(port),
      family_(AF_INET)
    {
        channelfd_ = socket(family_, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        if(channelfd_ < 0){
            LOG_FATAL("Socket::Socket(int port) : create socket fail");
        }
        addr_.sin_family = family_;
        addr_.sin_addr.s_addr = INADDR_ANY;
        addr_.sin_port = htons(port_);

        setReadEvents();
    }

Socket::~Socket() {
    if(closeFunc_){
        closeFunc_(this);
    }
    close(channelfd_);
}

void Socket::init(){
    int res = bind(channelfd_, (struct sockaddr*)&addr_, sizeof(addr_));
    if(res < 0){
        LOG_FATAL("Socket::bind() : bind fail");
    }

    res = listen(channelfd_, SOMAXCONN);
    if(res < 0){
        LOG_FATAL("Socket::listen() : listen fail");
    }
}

void Socket::handleRead() {
    struct sockaddr add;
    bzero(&add, sizeof(add));
    int con = accept4(channelfd_, &add, sizeof(add), SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(con < 0){
        int savedErrno = errno;
        switch (savedErrno)
        {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                // unexpected errors
                LOG_ERROR("unexpected error of Socket::accept() %d", errno);
                break;
            default:
                LOG_ERROR("unknown error of Socket::accept() %d", errno);
                break;
        }
    }
    if(readCallback_) {
        readCallback_(con);
    }
    else{
        close(con);
    }
}



