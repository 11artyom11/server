cmake_minimum_required(VERSION 2.8.9)
project (t_lib)

                    
include_directories(
                    "../../lib/include/helpers/",
                    "../../lib/include/util/cyptolib/" 
                    "../../lib/include/helpers/debug_helper/",
                    "../../lib/include/util/data_transfer/message_model/",
                    "../../lib/include/util/data_transfer/message_resolver/",
                    )

set (CMAKE_BINARY_DIR "./../../bin/tests/lib_tests/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")


#Message (JSON) model tests
add_executable(t_lib2 test2.cpp)
target_link_libraries(t_lib2 gtest_main)
target_link_libraries(t_lib2 message_model)
target_link_libraries(t_lib2 debug_helper)

#Message (JSON) resolver tests
add_executable(t_lib3 test3.cpp)
target_link_libraries(t_lib3 gtest_main)
target_link_libraries(t_lib3 message_model)
target_link_libraries(t_lib3 message_resolver)
target_link_libraries(t_lib3 debug_helper)
