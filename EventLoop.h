//
// Created by dell on 2017/5/18.
//

#ifndef PROJECT_EVENTLOOP_H
#define PROJECT_EVENTLOOP_H

#include<vector>

namespace simver{
    class EPoll;
    class Channel;
    typedef std::vector<Channel*> ChannelList;
    const int EPollTimeout = 10000;
    class EventLoop{
    public:
        EventLoop();
        ~EventLoop();
        void loop();
        void removeChannel(Channel*);

    private:
        ChannelList activeChannels_;
        EPoll* epoll_;
    };
}

#endif //PROJECT_EVENTLOOP_H
