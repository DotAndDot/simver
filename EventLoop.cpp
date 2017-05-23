//
// Created by dell on 2017/5/18.
//

#include "EPoll.h"
#include "log/log.h"

using namespace simver;

EventLoop::EventLoop()
    :epoll_(new EPoll()){}

void EventLoop::loop() {
    LOG_TRACE("start loop\n");
    while(1){
        activeChannels_.clear();
        epoll_->pollWait(EPollTimeout, activeChannels_);
        for(auto &it : activeChannels_){
            (*it)->handleEvent();
        }
    }
    LOG_TRACE("stop loop\n");
}