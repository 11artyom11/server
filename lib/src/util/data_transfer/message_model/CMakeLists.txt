cmake_minimum_required(VERSION 3.10)
project(message_model VERSION 1.0.1 DESCRIPTION "message_model description")
include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED message_model.cpp message_templates.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/message_model.h)
    
configure_file(message_model.pc.in message_model.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE ../../../../include/util/data_transfer)
target_include_directories(${PROJECT_NAME} PRIVATE ../../../../include/helpers)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

install(FILES ${CMAKE_BINARY_DIR}/message_model.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    
