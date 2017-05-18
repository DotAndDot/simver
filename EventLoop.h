//
// Created by dell on 2017/5/18.
//

#ifndef PROJECT_EVENTLOOP_H
#define PROJECT_EVENTLOOP_H

#include<vector>

namespace simver{
    class EPoll;
    const int EPollTimeout = 10000;
    class EventLoop{
    public:
        EventLoop();
        ~EventLoop();
        void loop();

    private:
        typedef std::vector<Channel*> ChannelList;
        ChannelList activeChannels_;
        EPoll* epoll_;
    };
}

#endif //PROJECT_EVENTLOOP_H
