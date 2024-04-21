#include "File.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>

File::File(EventLoop* loop, const std::string& filename) 
    : loop(loop), channel(loop, -1), filename(filename) {
    fd = open(filename.c_str(), O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        std::cerr << "Failed to open file: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
}

File::~File() {
    close(fd);
}

std::string File::read() {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        // 文件无法打开，返回空字符串
        return "";
    }

    // 读取文件内容
    std::string content((std::istreambuf_iterator<char>(fileStream)),
                        (std::istreambuf_iterator<char>()));

    fileStream.close();

    return content;
}

bool File::write(const std::string& data) {
    ssize_t bytesWritten = ::write(fd, data.c_str(), data.size());
    if (bytesWritten == -1) {
        std::cerr << "Failed to write to file: " << strerror(errno) << std::endl;
        return false;
    }
    std::cout << "Wrote " << bytesWritten << " bytes to file" << std::endl;
    return true;
}
