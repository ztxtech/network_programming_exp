#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "EventLoop.hpp"

class Channel {
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();
    void handleEvent();

private:
    EventLoop* loop;
    int fd;
};

#endif
