cmake_minimum_required(VERSION 2.8.9)
project (t_server)

set (CMAKE_BINARY_DIR "./../../bin/tests/server_tests/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

add_executable(t_server test_1.cpp)

target_link_libraries(t_server gtest_main)
