cmake_minimum_required(VERSION 2.8.9)
project (t_client)

set (CMAKE_BINARY_DIR "./../../bin/tests/client_tests/")
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

add_executable(t_client test_1.cpp)

target_link_libraries(t_client gtest_main)
target_link_libraries(t_client clientlib)
