cmake_minimum_required(VERSION 2.8.9)
project (server)


set (CMAKE_BINARY_DIR "./../../bin/server/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

add_executable(server src/main.cpp
                 src/server.cpp 
                    src/handler.cpp)


target_link_libraries( server debug_helper)

target_link_libraries( server crypto_unit)
