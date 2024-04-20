#include "EventLoop.h"
#include "gtest/gtest.h"
#include <thread>

// 测试EventLoop的基本运行
TEST(EventLoopTest, RunTest) {
    EventLoop loop;
    std::thread loop_thread([&]() { loop.run(); });

    // 添加一个延迟任务，等待1秒后输出信息
    loop.addEvent(loop.eventfd_, [] {
        std::cout << "EventLoop running..." << std::endl;
        // 模拟一个耗时操作
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    // 等待1秒钟确保EventLoop有足够时间运行
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 关闭EventLoop
    loop_thread.join();
}

// 测试添加和移除事件
TEST(EventLoopTest, AddRemoveEventTest) {
    EventLoop loop;
    std::thread loop_thread([&]() { loop.run(); });

    bool event_triggered = false;
    // 添加一个事件，在100毫秒后设置事件触发标志
    loop.addEvent(loop.eventfd_, [&] {
        event_triggered = true;
    });

    // 等待一段时间，然后移除事件
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    loop.removeEvent(loop.eventfd_);

    // 等待一段时间，确保事件不会被触发
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 检查事件触发标志是否为false
    ASSERT_FALSE(event_triggered);

    // 关闭EventLoop
    loop_thread.join();
}
