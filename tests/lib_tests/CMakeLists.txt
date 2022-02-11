cmake_minimum_required(VERSION 2.8.9)
project (t_lib)

set (CMAKE_BINARY_DIR "./../../bin/tests/lib_tests/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

add_executable(t_lib test_1.cpp)

target_link_libraries(t_lib gtest_main)
target_link_libraries(t_lib crypto_unit)
target_link_libraries(t_lib debug_helper)
