#ifndef SIMVER_CHANNEL_H
#define SIMVER_CHANNEL_H

namespace simver{

    class Channel{
    public:
        virtual int getEvents() = 0;
        virtual int getFd() = 0;

    };

}

#endif
