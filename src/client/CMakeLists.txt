cmake_minimum_required(VERSION 2.8.9)
project (client)


set (CMAKE_BINARY_DIR "./../../bin/client/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

include_directories(
                    "include/",
                    "../../lib/include",                    
                    "../../lib/include/helpers/",
                    "../../lib/include/util/cyptolib/",
                    "../../lib/include/helpers/debug_helper/",
                    "../../lib/include/util/data_transfer/message_model/",
                    "../../lib/include/util/data_transfer/message_resolver/",
                    "../../../lib/include/helpers/",
                    "../../../lib/include/helpers/debug_helper/"
                    )

add_executable(client src/main.cpp
                        src/client.cpp
                           src/communication_unit.cpp
                                src/connection_handler.cpp
                                    src/io_unit.cpp
                                        src/handler.cpp)

target_link_libraries( client debug_helper)
target_link_libraries( client message_model)
target_link_libraries( client message_resolver)
target_link_libraries( client crypto_unit)
