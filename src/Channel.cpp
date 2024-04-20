#include "Channel.h"

Channel::Channel() {}

Channel::~Channel() {}

void Channel::setReadCallback(std::function<void()> callback) {
    readCallback_ = std::move(callback);
}

void Channel::handleEvent() {
    // 读取事件发生，调用回调函数
    if (readCallback_) {
        readCallback_();
    }
}
