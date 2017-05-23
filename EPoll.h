//
// Created by gxh on 17-5-17.
//

#ifndef SIMVER_EPOLL_H
#define SIMVER_EPOLL_H

#include<vector>
#include<unordered_map>
#include"EventLoop.h"


const int initEventSize = 20;

struct epoll_event;

namespace simver{
    class Channel;
    class EPoll{
    public:
        EPoll();
        ~EPoll();
        void updateCtl(int op, Channel* channel);
        void addChannel(Channel* channel);
        void delChannel(Channel* channel);
        void pollWait(int timeout, ChannelList& channels);
        const char* operationToString(int op);

    private:
        int epollfd_;
        typedef std::vector<struct epoll_event> EventList;
        EventList eventList_;
        typedef std::unordered_map<int, Channel*> ChannelMap;
        ChannelMap channelMap_;
    };
}

#endif //SIMVER_EPOLL_H
