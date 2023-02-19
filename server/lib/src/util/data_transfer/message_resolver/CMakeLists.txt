cmake_minimum_required(VERSION 3.9)
project(message_resolver VERSION 1.0.1 DESCRIPTION "message_resolver description")

set(OUT_DIR ../../../../../bin/libs)
find_package(OpenSSL REQUIRED)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_library(nlohmann_json nlohmann_json)


include(GNUInstallDirs)
include_directories(../../../../include/util/data_transfer/message_resolver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR})

add_library(message_resolver SHARED message_resolver.cpp)
set_target_properties(message_resolver PROPERTIES VERSION ${PROJECT_VERSION})

target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} nlohmann_json)
