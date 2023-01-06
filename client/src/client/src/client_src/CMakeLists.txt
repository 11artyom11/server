cmake_minimum_required(VERSION 2.8.9)
project (client_lib)

add_library(client_lib SHARED client.cpp
communication_unit.cpp
connection_handler.cpp
io_unit.cpp
handler.cpp
chatroom_model.cpp)

target_include_directories(client_lib PUBLIC "../../include/",
                    "../../../../lib/include",
                    "../../../../lib/include/util/cyptolib/",
                    "../../../../lib/include/util/data_transfer/message_model/",
                    "../../../../lib/include/util/data_transfer/message_resolver/",
                    "../../../../lib/include/helpers/",
                    "../../../../lib/include/helpers/debug_helper")


target_link_libraries( client_lib debug_helper)
target_link_libraries( client_lib message_model)
target_link_libraries( client_lib message_resolver)
