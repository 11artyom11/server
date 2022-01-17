cmake_minimum_required(VERSION 3.9)
project(libdebug_helper VERSION 1.0.1 DESCRIPTION "libdebug_helper description")
include(GNUInstallDirs)

add_library(libdebug_helper SHARED debug_helper/debug_helper.cpp)

set_target_properties(libdebug_helper PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/libdebug_helper.h)
    
configure_file(libdebug_helper.pc.in libdebug_helper.pc @ONLY)
target_include_directories(libdebug_helper PRIVATE .)
install(TARGETS libdebug_helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/libdebug_helper.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)