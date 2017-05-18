//
// Created by gxh on 2017/5/17.
//

#include "Channel.h"
#include <sys/epoll.h>
#include <sstream>
#include "log/log.h"

using namespace simver;

const int Channel::NoneEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

string Channel::eventsToString()
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
    if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
    {
        closeCallback();
    }

    if (revents_ & POLLNVAL)
    {
         LOG_WARN("fd = %d Channel::handle_event() POLLNVAL\n", channelfd_);
    }

    if (revents_ & (POLLERR | POLLNVAL))
    {
        errorCallback();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        readCallback();
    }
    if (revents_ & POLLOUT)
    {
        writeCallback();
    }
}