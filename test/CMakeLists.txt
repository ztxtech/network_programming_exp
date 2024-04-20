add_executable(test_EventLoop test_EventLoop.cpp)
add_executable(test_File test_File.cpp)

# 链接Google Test库
target_link_libraries(test_EventLoop gtest gtest_main)
target_link_libraries(test_File gtest gtest_main)

# 链接IO ring和Event Loop
target_link_libraries(test_EventLoop io_uring)
target_link_libraries(test_File io_uring)

# 添加测试
add_test(NAME EventLoopTest COMMAND test_EventLoop)
add_test(NAME FileTest COMMAND test_File)
