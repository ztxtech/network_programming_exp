#include "File.h"
#include "gtest/gtest.h"
#include <fstream>

// 测试文件读取
TEST(FileTest, ReadTest) {
    // 创建测试文件
    std::ofstream outfile("test.txt");
    outfile << "Hello, world!";
    outfile.close();

    // 读取测试文件内容
    File file("test.txt");
    std::string data;
    file.setReadCallback([&] {
        data = file.getData();
    });

    // 等待一段时间，以便Channel能够处理读取事件
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 检查读取的数据是否正确
    ASSERT_EQ(data, "Hello, world!");
}

// 测试文件写入
TEST(FileTest, WriteTest) {
    File file("test_write.txt");

    // 写入数据
    std::string data = "Hello, world!";
    file.write(data);

    // 读取写入的文件内容
    std::ifstream infile("test_write.txt");
    std::string read_data;
    std::getline(infile, read_data);

    // 检查读取的数据是否正确
    ASSERT_EQ(read_data, data);
}
