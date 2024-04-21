#include "EventLoop.hpp"
#include <iostream>
#include <cstring>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <errno.h>


EventLoop::EventLoop() {
    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        std::cerr << "Failed to create epoll: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize io_uring
    if (io_uring_queue_init(128, &ring, 0) < 0) {
        std::cerr << "Failed to initialize io_uring: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create eventfd
    event_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (event_fd == -1) {
        std::cerr << "Failed to create eventfd: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Add eventfd to epoll
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = event_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, event_fd, &ev) == -1) {
        std::cerr << "Failed to add eventfd to epoll: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
}

EventLoop::~EventLoop() {
    close(epollfd);
    close(event_fd);
    io_uring_queue_exit(&ring);
}

void EventLoop::run() {
    running = true;
    while (running) {
        processEvents();
    }
}

void EventLoop::addEvent(int fd, unsigned int events, std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(mtx);
    this->events.push_back({fd, events, callback}); 
}



void EventLoop::removeEvent(int fd) {
    std::lock_guard<std::mutex> lock(mtx);
    events.erase(std::remove_if(events.begin(), events.end(), [fd](const Event& e) { return e.fd == fd; }), events.end());
}

void EventLoop::stop() {
    running = false;
}

void EventLoop::processEvents() {
    struct epoll_event evlist[16];
    int n = epoll_wait(epollfd, evlist, 16, -1);
    if (n == -1) {
        std::cerr << "Failed to epoll_wait: " << strerror(errno) << std::endl;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (evlist[i].data.fd == event_fd) {
            uint64_t dummy;
            if (read(event_fd, &dummy, sizeof(dummy)) == -1) {
                std::cerr << "Failed to read eventfd: " << strerror(errno) << std::endl;
            }
        } else {
            std::lock_guard<std::mutex> lock(mtx);
            for (auto& event : events) {
                if (event.fd == evlist[i].data.fd) {
                    if (event.callback) event.callback();
                }
            }
        }
    }
}
