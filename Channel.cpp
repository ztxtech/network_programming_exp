#include "Channel.hpp"
#include "EventLoop.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

Channel::Channel(EventLoop* loop, int fd) : loop(loop), fd(fd) {
    loop->addEvent(fd, EPOLLIN, [this]() { this->handleEvent(); });
}

Channel::~Channel() {
    loop->removeEvent(fd);
}

void Channel::handleEvent() {
    std::cout << "Event occurred on file descriptor: " << fd << std::endl;
}
