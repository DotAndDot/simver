//
// Created by gxh on 17-5-17.
//
#include <unistd.h>
#include <string.h>
#include "EPoll.h"
#include "log/log.h"

using namespace simver;

EPoll::EPoll()
    :eventList_(initEventSize){
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
    if(epollfd_ < 0){
        LOG_ERROR("Epoll::EPoll() : create epoll fail");
    }
}

EPoll::~EPoll(){
    close(epollfd_);
}

void EPoll::updateCtl(int op, Channel *channel) {
    struct epoll_event event;
    int fd = channel->getFd();
    bzero(&event, sizeof(event));
    event.events = channel->getEvents();
    event.data.ptr = channel;
    event.data.fd = fd;
    int res = epoll_ctl(epollfd_, op, fd, event);
}

void EPoll::addChannel(Channel *channel) {

}

const char* operationToString(int op){
    switch(op){
        case EPOLL_CTL_ADD:
            return "ADD";
        case EPOLL_CTL_DEL:
            return "DEL";
        case EPOLL_CTL_MOD:
            return "MOD";
        default:
            assert(false && "ERROR op");
            return "Unknown Operation";
    }
}