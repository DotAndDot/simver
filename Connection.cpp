//
// Created by dell on 2017/5/19.
//

#include "Connection.h"
#include "log/log.h"

#include <unistd.h>

using namespace simver;

Connection::Connection(std::string name, int fd)
    :Channel(0,fd),
    name_(name){
    setReadEvents();
}

void Connection::send(Buffer* buf){
    const void* data = buf->peek();
    size_t len = buf->readableBytes();
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    // if no thing in output queue, try writing directly
    if (!isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = write(channelfd_, data, len);
        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            if (remaining == 0 && writeCompleteCallback_)
            {
               writeCompleteCallback_(this);
            }
        }
        else // nwrote < 0
        {
            nwrote = 0;
            if (errno != EWOULDBLOCK)
            {
                LOG_ERROR("TcpConnection::sendInLoop");
                if (errno == EPIPE || errno == ECONNRESET) // FIXME: any others?
                {
                    faultError = true;
                }
            }
        }
    }

    assert(remaining <= len);
    if (!faultError && remaining > 0)
    {
        outputBuffer_.append(static_cast<const char*>(data)+nwrote, remaining);
        if (!isWriting())
        {
            enableWriting();
            updateConnection_(getEvents(), this);
        }
    }
}

void Connection::handleRead(){
    int saveErrno = 0;
    ssize_t n = inputBuffer_.readFd(channelfd_, &saveErrno);
    if(n > 0){
        messageCallback_(this);
    }
    else if(n == 0){
        handleClose();
    }
    else{
        LOG_ERROR("Connection::handleRead");
        handleError();
    }
}

void Connection::handleWrite() {
    if(isWriting()){
        ssize_t n = write(channelfd_, outputBuffer_.peek(), outputBuffer_.readableBytes());
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                disableWriting();
                if (writeCompleteCallback_)
                {
                    writeCompleteCallback_(this);
                }
            }
        }
        else
        {
            LOG_ERROR("Connection::handleWrite");
        }
    }
    else
    {
        LOG_TRACE("Connection fd = %d is down, no more writing", channelfd_);
    }

}

void Connection::handleClose() {
    closeCallback_(this);
}

void Connection::handleError() {
    LOG_ERROR("Connectin::handleError errno = %d", errno);
}
