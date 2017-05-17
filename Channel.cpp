//
// Created by gxh on 2017/5/17.
//

#include "Channel.h"
#include <sys/epoll.h>

using namespace simver;

const int Channel::NoneEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

