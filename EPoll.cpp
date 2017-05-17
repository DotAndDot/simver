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

}

void EPoll::addChannel(Channel *channel) {

}
