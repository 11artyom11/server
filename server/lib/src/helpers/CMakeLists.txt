cmake_minimum_required(VERSION 3.9)
project(debug_helper VERSION 1.0.1 DESCRIPTION "debug_helper description")
include(GNUInstallDirs)

add_library(debug_helper SHARED debug/debug_helper.cpp)

set_target_properties(debug_helper PROPERTIES VERSION ${PROJECT_VERSION})

