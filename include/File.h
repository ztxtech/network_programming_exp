#ifndef FILE_H
#define FILE_H

#include <string>
#include <functional>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Channel.h"

class File {
public:
    File(const std::string& filename);
    ~File();

    void read();
    void write(const std::string& data);

    void setReadCallback(std::function<void()> callback);

private:
    int fd_;
    std::string filename_;
    std::string buffer_; // 用于读写数据
    Channel channel_;
};
#endif
