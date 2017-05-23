#ifndef SIMVER_CHANNEL_H
#define SIMVER_CHANNEL_H

#include <string>
#include<functional>

namespace simver{

    class Channel{
    public:
        typedef std::function<void (int)> ReadEventCallback;
        typedef std::function<void (Channel*)> CloseEventCallback;
        Channel(int ev, int fd) : events_(ev), channelfd_(fd), curevent_(0){}
        virtual ~Channel();
        int getEvents(){ return events_;}
        int getFd() { return channelfd_; }
        void setCurevent(int ev){ curevent_ = ev; }
        void setReadEvents(){ events_ = ReadEvent;}
        void setWriteEvents() { events_ = WriteEvent;}
        void setNoneEvents() {events_ = NoneEvent;}
        void handleEvent();
        virtual void handleClose();
        virtual void handleError();
        virtual void handleRead();
        virtual void handleWrite();

        void setReadCallback(const ReadEventCallback& cb){ readCallback_ = cb; }
        void setCloseCallback(const CloseEventCallback& cb){ closeCallback_ = cb;}

        std::string eventsToString();

    protected:
        int events_;
        int channelfd_;
        int curevent_;
        static const int NoneEvent;
        static const int ReadEvent;
        static const int WriteEvent;

        ReadEventCallback readCallback_;
        CloseEventCallback closeCallback_;
    };

}

#endif
