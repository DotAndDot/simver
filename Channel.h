#ifndef SIMVER_CHANNEL_H
#define SIMVER_CHANNEL_H

namespace simver{

    class Channel{
    public:
        Channel(int ev, int fd) : events_(ev), channelfd_(fd){}
        virtual ~Channel();
        int getEvents(){ return events_;}
        void setReadEvents(){ events_ = ReadEvent;}
        void setWriteEvents() { events_ = WriteEvent;}
        void setNoneEvents() {events_ = NoneEvent;}
        int getFd() { return channelfd_; }

    protected:
        int events_;
        int channelfd_;
        static const int NoneEvent;
        static const int ReadEvent;
        static const int WriteEvent;
    };

}

#endif
