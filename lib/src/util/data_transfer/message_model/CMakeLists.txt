cmake_minimum_required(VERSION 3.9)
project(message_model VERSION 1.0.1 DESCRIPTION "message_model description")
include(GNUInstallDirs)

add_library(message_model SHARED message_model.cpp message_templates.cpp)

set_target_properties(message_model PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/message_model.h)
    
configure_file(message_model.pc.in message_model.pc @ONLY)
target_include_directories(message_model PRIVATE .)
install(TARGETS message_model
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
include_directories(../../../../../outter_modules/json/single_include/nlohmann)
target_link_libraries(${PROJECT_NAME} -L../../../../../outter_modules/json)


install(FILES ${CMAKE_BINARY_DIR}/message_model.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    