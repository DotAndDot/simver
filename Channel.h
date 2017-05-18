#ifndef SIMVER_CHANNEL_H
#define SIMVER_CHANNEL_H

namespace simver{

    class Channel{
    public:
        Channel(int ev, int fd) : events_(ev), channelfd_(fd), curevent_(0){}
        virtual ~Channel();
        int getEvents(){ return events_;}
        int getFd() { return channelfd_; }
        void setCurevent(int ev){ curevent_ = ev; }
        void setReadEvents(){ events_ = ReadEvent;}
        void setWriteEvents() { events_ = WriteEvent;}
        void setNoneEvents() {events_ = NoneEvent;}
        void handleEvent();
        virtual closeCallback();
        virtual errorCallback();
        virtual readCallback();
        virtual writeCallback();

        string eventsToString();

    protected:
        int events_;
        int channelfd_;
        int curevent_;
        static const int NoneEvent;
        static const int ReadEvent;
        static const int WriteEvent;
    };

}

#endif
