//
// Created by gxh on 2017/5/17.
//

#include "Channel.h"
#include <sys/epoll.h>
#include <sstream>
#include <bits/poll.h>
#include "log/log.h"

using namespace simver;

const int Channel::NoneEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

std::string Channel::eventsToString()
{
    std::ostringstream oss;
    oss << channelfd_ << ": ";
    if (events_ & POLLIN)
        oss << "IN ";
    if (events_ & POLLPRI)
        oss << "PRI ";
    if (events_ & POLLOUT)
        oss << "OUT ";
    if (events_ & POLLHUP)
        oss << "HUP ";
    if (events_ & POLLRDHUP)
        oss << "RDHUP ";
    if (events_ & POLLERR)
        oss << "ERR ";
    if (events_ & POLLNVAL)
        oss << "NVAL ";

    return oss.str().c_str();
}

void Channel::handleEvent(){
    if ((curevent_ & POLLHUP) && !(curevent_ & POLLIN))
    {
        handleClose();
    }

    if (curevent_ & POLLNVAL)
    {
         LOG_WARN("fd = %d Channel::handle_event() POLLNVAL\n", channelfd_);
    }

    if (curevent_ & (POLLERR | POLLNVAL))
    {
        handleError();
    }
    if (curevent_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        handleRead();
    }
    if (curevent_ & POLLOUT)
    {
        handleWrite();
    }
}
