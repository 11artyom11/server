cmake_minimum_required(VERSION 2.8.9)
project (t_lib)

set (CMAKE_BINARY_DIR "./../../bin/tests/lib_tests/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "-g -w -O2 -pthread")

#Crypto tests
add_executable(t_lib test_1.cpp)
target_link_libraries(t_lib gtest_main)
target_link_libraries(t_lib crypto_unit)
target_link_libraries(t_lib debug_helper)

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

