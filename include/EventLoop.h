#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <functional>
#include <unistd.h>
#include <sys/eventfd.h>
#include <sys/io_uring.h>
#include "Channel.h"

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    void run();

    // 添加事件到EventLoop
    void addEvent(int fd, std::function<void()> callback);

    // 从EventLoop中移除事件
    void removeEvent(int fd);

private:
    int eventfd_;
    int iouring_;
    std::unordered_map<int, std::function<void()>> events_; // 存储事件回调函数
    Channel channel_; // 用于监听eventfd
};
#endif
