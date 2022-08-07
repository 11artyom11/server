cmake_minimum_required(VERSION 3.9)
project(debug_helper VERSION 1.0.1 DESCRIPTION "debug_helper description")
include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED debug/debug_helper.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/debug_helper.h)
    
configure_file(debug_helper.pc.in debug_helper.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE ../../include/helpers)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/debug_helper.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
