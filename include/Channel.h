#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <sys/poll.h>

class Channel {
public:
    Channel();
    ~Channel();

    void setReadCallback(std::function<void()> callback);

    void handleEvent();

private:
    int fd_;
    std::function<void()> readCallback_;
};
#endif
