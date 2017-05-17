//
// Created by gxh on 17-5-17.
//

#ifndef SIMVER_EPOLL_H
#define SIMVER_EPOLL_H

#include<vector>
#include<sys/epoll.h>
#include <bits/unordered_map.h>
#include "Channel.h"

const int initEventSize = 20;

struct epoll_event;

namespace simver{
    class EPoll{
    public:
        EPoll();
        ~EPoll();
        void updateCtl(int op, Channel* channel);
        void addChannel(Channel* channel);

    private:
        int epollfd_;
        typedef std::vector<struct epoll_event> EventList;
        EventList eventList_;
        typedef std::unordered_map<int, Channel*> ChannelMap;
        ChannelMap channelMap_;
    };
}

#endif //SIMVER_EPOLL_H
