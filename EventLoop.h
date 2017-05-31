//
// Created by dell on 2017/5/18.
//

#ifndef PROJECT_EVENTLOOP_H
#define PROJECT_EVENTLOOP_H

#include<vector>
#include<memory>

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
        void addChannel(Channel* channel);
        void removeChannel(Channel* channel);
        void updateChannel(int op, Channel* channel);

    private:
        ChannelList activeChannels_;
        std::unique_ptr<EPoll> epoll_;
    };
}

#endif //PROJECT_EVENTLOOP_H
