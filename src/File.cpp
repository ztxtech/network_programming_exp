#include "File.h"

File::File(const std::string& filename) : filename_(filename) {
    fd_ = open(filename_.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_ == -1) {
        // 处理文件打开失败的情况
    }
    channel_.setReadCallback([this] { this->read(); }); // 设置channel的回调函数为read
    addEvent(fd_, [this] { channel_.handleEvent(); }); // 添加文件描述符的监听事件
}

File::~File() {
    close(fd_);
}

void File::read() {
    ssize_t bytes_read = read(fd_, buffer_.data(), buffer_.size());
    if (bytes_read > 0) {
        // 处理读取成功的情况
    } else if (bytes_read == 0) {
        // 文件已读到末尾
    } else {
        // 处理读取失败的情况
    }
}

void File::write(const std::string& data) {
    ssize_t bytes_written = write(fd_, data.data(), data.size());
    if (bytes_written > 0) {
        // 处理写入成功的情况
    } else {
        // 处理写入失败的情况
    }
}

void File::setReadCallback(std::function<void()> callback) {
    channel_.setReadCallback(callback);
}
