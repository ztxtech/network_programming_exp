#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include <liburing.h>
#include <functional>
#include <vector>
#include <mutex>

class EventLoop {
public:
    EventLoop();
    ~EventLoop();
    void run();
    void addEvent(int fd, unsigned int events, std::function<void()> callback);
    void removeEvent(int fd);
    void stop();

private:
    struct Event {
        int fd;
        unsigned int events;
        std::function<void()> callback;
    };

    int epollfd;
    bool running;
    std::mutex mtx;
    std::vector<Event> events; 
    struct io_uring ring;
    int event_fd;

    void processEvents();
};

#endif // EVENTLOOP_HPP
