cmake_minimum_required(VERSION 2.8.9)

#project name : client_server
project (client_server)

#adding subproject server 
add_subdirectory( src/server/ ./bin/server)

#adding subproject client
add_subdirectory( src/client/ ./bin/client)

#adding shared lib 
add_subdirectory(lib/src/helpers)
