cmake_minimum_required(VERSION 3.10)

project(iouring_project)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
file(GLOB SRC_FILES "src/*.cpp")

# 添加头文件路径
include_directories(include)

# 添加可执行文件
add_executable(iouring_test ${SRC_FILES})

# 链接IO ring和Event Loop
target_link_libraries(iouring_test io_uring)

# 添加测试
enable_testing()
add_subdirectory(test)
