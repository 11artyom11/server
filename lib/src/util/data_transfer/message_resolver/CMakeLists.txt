cmake_minimum_required(VERSION 3.9)
project(message_resolver VERSION 1.0.1 DESCRIPTION "message_resolver description")
include(GNUInstallDirs)

add_library(message_resolver SHARED message_resolver.cpp)

include_directories(../../../../include/util/data_transfer/message_resolver)

set_target_properties(message_resolver PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/message_resolver.h)
    
configure_file(message_resolver.pc.in message_resolver.pc @ONLY)
target_include_directories(message_resolver PRIVATE .)
install(TARGETS message_resolver
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} -L../../../../../outter_modules/json)


install(FILES ${CMAKE_BINARY_DIR}/message_resolver.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    