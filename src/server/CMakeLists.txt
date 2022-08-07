cmake_minimum_required(VERSION 3.10)
project (server)

set (CMAKE_BINARY_DIR "./../../bin/server/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp
    src/server.cpp
    src/handler.cpp
    src/customer_model/customer.cpp
    src/customer_model/customer_crypto_unit.cpp
    src/chat_model/chatroom_model.cpp
    src/chat_model/chatroom_manager.cpp
)                     

target_include_directories(${PROJECT_NAME} PRIVATE
    "include/"
    "include/customer_model/"
    "../../lib/include/util/cyptolib/"
    "../../lib/include/helpers/debug_helper/"
    "../../lib/include/util/data_transfer/message_model/"
    "../../lib/include/util/data_transfer/message_resolver/"
    "include/chat_model"
)

target_link_libraries(${PROJECT_NAME} PRIVATE message_model)
target_link_libraries(${PROJECT_NAME} PRIVATE message_resolver)
target_link_libraries(${PROJECT_NAME} PRIVATE debug_helper)
target_link_libraries(${PROJECT_NAME} PRIVATE crypto_unit)
target_link_libraries(${PROJECT_NAME} PRIVATE message_model)
target_link_libraries(${PROJECT_NAME} PRIVATE message_resolver)
