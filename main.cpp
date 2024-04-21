#include "EventLoop.hpp"
#include "File.hpp"
#include <iostream>

int main() {
    EventLoop loop;

    // 创建一个文件对象，并向文件中写入数据
    File file(&loop, "test.txt");
    file.write("Hello, World!");

    // 读取文件内容
    file.read();

    // 运行事件循环
    loop.run();

    return 0;
}
