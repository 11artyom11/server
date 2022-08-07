cmake_minimum_required(VERSION 3.10)
project (client)

set (CMAKE_BINARY_DIR "./../../bin/client/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp
    src/client.cpp
    src/communication_unit.cpp
    src/connection_handler.cpp
    src/io_unit.cpp
    src/handler.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    "include"
    "../../lib/include"
    "../../lib/include/helpers/"
    "../../lib/include/util/cyptolib/"
    "../../lib/include/helpers/debug_helper/"
    "../../lib/include/util/data_transfer/message_model/"
    "../../lib/include/util/data_transfer/message_resolver/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE debug_helper)
target_link_libraries(${PROJECT_NAME} PRIVATE message_model)
target_link_libraries(${PROJECT_NAME} PRIVATE message_resolver)
target_link_libraries(${PROJECT_NAME} PRIVATE crypto_unit)
