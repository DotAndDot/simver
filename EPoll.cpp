//
// Created by gxh on 17-5-17.
//
#include <unistd.h>
#include <strings.h>
#include <sys/epoll.h>
#include <error.h>
#include <assert.h>
#include <string.h>
#include "EPoll.h"
#include "log/log.h"
#include "Channel.h"

using namespace simver;

EPoll::EPoll()
    :eventList_(initEventSize){
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
    if(epollfd_ < 0){
        LOG_FATAL("Epoll::EPoll() : create epoll fail");
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
    if( epoll_ctl(epollfd_, op, fd, event) < 0 ){
        LOG_ERROR("epoll_ctl op = %s, fd = %d", operationToString(op), fd);
    }
}

void EPoll::addChannel(Channel *channel) {
    int fd = channel->getFd();
    assert( channelMap_.find(fd) == channelMap_.end() );
    channelMap_[fd] = channel;
    updateCtl(EPOLL_CTL_ADD, channel);
}

void EPoll::delChannel(Channel *channel) {
    int fd = channel->getFd();
    assert( channelMap_.find(fd) != channelMap_.end() );
    updateCtl(EPOLL_CTL_DEL, channel);
    channelMap_.erase(fd);
}

void EPoll::pollWait(int timeout, ChannelList* activeChannels) {
    int num = epoll_wait(epollfd_, &*eventList_.begin(), static_cast<int>(eventList_.size()), timeout);
    if(num > 0){
        for(int i = 0; i < num; i++){
            Channel* channel = static_cast<Channel*>(eventList_[i].data.ptr);
            int fd = channel->getFd();
            assert(channelMap_.find(fd) != channelMap_.end());
            assert(channelMap_[fd] == channel);
            channel->setCurevent(eventList_[i].events);
            activeChannels->push_back(channel);
        }
        if(num == eventList_.size()){
            eventList_.resize(eventList_.size() * 2);
        }
    }
    else if(num == 0){
        LOG_TRACE("nothing happen");
    }
    else{
        LOG_ERROR("EPoll::pollWait()  error = %d message = %s", errno, strerror(errno));
    }
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