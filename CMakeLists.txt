cmake_minimum_required(VERSION 2.8.9)


#project name : client_server
project (client_server)

#adding subproject server 
add_subdirectory( src/server/ ./bin/server)

#adding subproject client
add_subdirectory( src/client/ ./bin/client)

add_subdirectory(outter_modules/json)

#adding shared lib helpers
add_subdirectory(lib/src/helpers)

#adding shared lib utilities
add_subdirectory(lib/src/util)

#adding unit tests
add_subdirectory(tests)
