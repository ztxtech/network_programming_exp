#include "EventLoop.h"

EventLoop::EventLoop() {
    eventfd_ = eventfd(0, EFD_NONBLOCK);
    iouring_ = io_uring_fd();
    channel_.setReadCallback([this] { this->run(); }); // 设置channel的回调函数为run
    addEvent(eventfd_, [this] { channel_.handleEvent(); }); // 添加eventfd的监听事件
}

EventLoop::~EventLoop() {
    close(eventfd_);
    close(iouring_);
}

void EventLoop::run() {
    for (;;) {
        // 在这里实现事件循环
        struct io_uring_cqe *cqe;
        int ret = io_uring_wait_cqe(iouring_, &cqe);
        if (ret < 0) {
            // 处理错误
            break;
        }
        // 调用对应事件的回调函数
        events_[cqe->user_data]();
        io_uring_cqe_seen(iouring_, cqe);
    }
}

void EventLoop::addEvent(int fd, std::function<void()> callback) {
    // 将回调函数加入到事件映射中
    events_[fd] = callback;
    // 将事件添加到IO ring
    struct io_uring_sqe *sqe = io_uring_get_sqe(iouring_);
    io_uring_prep_poll_add(sqe, fd, POLLIN);
    io_uring_sqe_set_data(sqe, fd); // 将文件描述符作为用户数据传递给事件处理函数
    io_uring_submit(iouring_);
}

void EventLoop::removeEvent(int fd) {
    // 从事件映射中移除对应事件
    events_.erase(fd);
    // 将事件从IO ring中移除
    struct io_uring_sqe *sqe = io_uring_get_sqe(iouring_);
    io_uring_prep_poll_remove(sqe, fd);
    io_uring_sqe_set_data(sqe, fd); // 将文件描述符作为用户数据传递给事件处理函数
    io_uring_submit(iouring_);
}
