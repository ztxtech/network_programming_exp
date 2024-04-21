#ifndef FILE_HPP
#define FILE_HPP

#include "EventLoop.hpp"
#include <string>

class Channel {
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();
    void handleEvent();

private:
    EventLoop* loop;
    int fd;
};

class File {
public:
    File(EventLoop* loop, const std::string& filename);
    ~File();
    std::string read();
    bool write(const std::string& data);

private:
    EventLoop* loop;
    Channel channel;
    std::string filename;
    int fd;

    void handleRead();
    void handleWrite();
};

#endif // FILE_HPP
