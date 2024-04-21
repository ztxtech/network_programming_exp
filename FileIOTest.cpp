#include "gtest/gtest.h"
#include "EventLoop.hpp"
#include "File.hpp"

// 定义测试类
class FileTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例运行之前执行
        loop = new EventLoop();
        file = new File(loop, "test.txt");
    }

    void TearDown() override {
        // 在每个测试用例运行之后执行
        delete file;
        delete loop;
    }

    // 声明成员变量
    EventLoop* loop;
    File* file;
};

// 测试文件读写功能
TEST_F(FileTest, ReadWriteTest) {
    std::string content = "Hello, World!";
    EXPECT_TRUE(file->write(content)) << "Failed to write to file";

    std::string result = file->read();
    EXPECT_FALSE(result.empty()) << "Failed to read from file";
    
    EXPECT_EQ(content, result);
}

// 运行所有测试
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
