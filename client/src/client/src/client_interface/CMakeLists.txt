cmake_minimum_required(VERSION 2.8.9)
project (client_interface)


add_library(client_interface SHARED client_interface.cpp)

target_include_directories(client_interface PUBLIC "../../include/client_interface", "../../../../lib/include/helpers")
