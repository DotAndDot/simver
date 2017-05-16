#include "Socket.h"
#include <sys/socket.h>

using namespace simver;

Socket::Socket(int port)
    : port_(port){
        sockfd_ = socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    }
