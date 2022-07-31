cmake_minimum_required(VERSION 2.8.9)


#project name : client_server
project (client_server)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


include(CTest)

#adding subproject server 
add_subdirectory( src/server/ ./bin/server)


#adding subproject client
add_subdirectory( src/client/ ./bin/client)

add_subdirectory(3rdparty/json)

#adding shared lib helpers
add_subdirectory(lib/src/helpers)

#adding shared lib utilities
add_subdirectory(lib/src/util)

#adding unit tests
add_subdirectory(tests)

#add tests to Cmake config
add_test(NAME MessageModelEncryptiontest COMMAND bin/tests/lib_tests/t_lib4)
