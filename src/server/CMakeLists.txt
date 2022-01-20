cmake_minimum_required(VERSION 2.8.9)
project (server)


set (CMAKE_BINARY_DIR "./../../bin/server/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w")
add_executable(server src/server.cpp src/main.cpp)

target_link_libraries( server libdebug_helper)
