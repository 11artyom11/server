cmake_minimum_required(VERSION 3.9)
project(debug_helper VERSION 1.0.1 DESCRIPTION "debug_helper description")
include(GNUInstallDirs)

add_library(debug_helper SHARED debug/debug_helper.cpp)

set_target_properties(debug_helper PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/debug_helper.h)
    
configure_file(debug_helper.pc.in debug_helper.pc @ONLY)
target_include_directories(debug_helper PRIVATE .)
install(TARGETS debug_helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/debug_helper.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    