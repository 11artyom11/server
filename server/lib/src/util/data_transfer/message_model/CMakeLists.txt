cmake_minimum_required(VERSION 3.9)
project(message_model VERSION 1.0.1 DESCRIPTION "message_model description")
include(GNUInstallDirs)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_library(nlohmann_json nlohmann_json)

include_directories(../../../../../3rdparty/json/single_include/nlohmann)

add_library(message_model SHARED message_model.cpp message_templates.cpp)
set_target_properties(message_model PROPERTIES VERSION ${PROJECT_VERSION})

target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} nlohmann_json)
