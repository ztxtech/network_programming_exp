cmake_minimum_required(VERSION 3.10)
project(FileIOUsingLiburing)

set(CMAKE_CXX_STANDARD 17)

# Add executable for main program
add_executable(FileIOUsingLiburing main.cpp EventLoop.cpp Channel.cpp File.cpp)

# Link liburing
find_library(LIBURING_LIBRARIES NAMES uring PATHS /usr/local/lib /usr/lib)
if (LIBURING_LIBRARIES)
    target_link_libraries(FileIOUsingLiburing ${LIBURING_LIBRARIES})
else()
    message(FATAL_ERROR "liburing library not found")
endif()

# Add executable for tests
add_executable(FileIOTest FileIOTest.cpp EventLoop.cpp File.cpp Channel.cpp)

# Link liburing and Google Test
find_package(GTest REQUIRED)
target_link_libraries(FileIOTest ${LIBURING_LIBRARIES} ${GTEST_BOTH_LIBRARIES})