cmake_minimum_required(VERSION 3.10)
project(message_resolver VERSION 1.0.1 DESCRIPTION "message_resolver description")
include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED message_resolver.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/message_resolver.h)
    
configure_file(message_resolver.pc.in message_resolver.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE ../../../../include/helpers)
target_include_directories(${PROJECT_NAME} PRIVATE  ../../../../include/util/data_transfer)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE  nlohmann_json::nlohmann_json)

install(FILES ${CMAKE_BINARY_DIR}/message_resolver.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    
