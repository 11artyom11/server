cmake_minimum_required(VERSION 3.12) # version can be different

project(tests) #name of project

add_subdirectory(googletest)    # add googletest subdirectory
add_subdirectory(client_tests)  # add tests for client side subdirectory
add_subdirectory(lib_tests)     # add tests for libraries subdirectory
add_subdirectory(server_tests)  # add tests for server side subdirectory

# include_directories(googletest/googletest/include) # this is so we can #include <gtest/gtest.h>
# include_directories(../src/client/include)
# include_directories(../src/server/include)
# include_directories(../lib/include)

