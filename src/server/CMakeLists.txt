cmake_minimum_required(VERSION 2.8.9)
project (server)


set (CMAKE_BINARY_DIR "./../../bin/server/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

add_executable(server src/main.cpp
                 src/server.cpp 
                    src/handler.cpp
                        src/customer_model/customer.cpp
                           src/customer_model/customer_crypto_unit.cpp )

target_link_libraries( server message_model)
target_link_libraries( server message_resolver)


target_link_libraries( server debug_helper)

target_link_libraries( server crypto_unit)
