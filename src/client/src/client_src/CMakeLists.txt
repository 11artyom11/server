cmake_minimum_required(VERSION 2.8.9)
project (client)

add_library(client SHARED client.cpp
communication_unit.cpp
connection_handler.cpp
io_unit.cpp
handler.cpp
)

target_include_directories(client PUBLIC "../../include/",
                    "../../../../lib/include",
                    "../../../../lib/include/util/cyptolib/",
                    "../../../../lib/include/util/data_transfer/message_model/",
                    "../../../../lib/include/util/data_transfer/message_resolver/",
                    "../../../../lib/include/helpers/",
                    "../../../../lib/include/helpers/debug_helper"
)


target_link_libraries( client debug_helper)
target_link_libraries( client message_model)
target_link_libraries( client message_resolver)
