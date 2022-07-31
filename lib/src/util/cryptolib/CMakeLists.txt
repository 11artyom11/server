cmake_minimum_required(VERSION 3.9)
project(crypto_unit VERSION 1.0.1 DESCRIPTION "crypto_unit description")
include(GNUInstallDirs)

include_directories("../../../include/util/cyptolib/")
add_library(crypto_unit SHARED crypto_unit.cpp)

set_target_properties(crypto_unit PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/crypto_unit.h)
    
SET(GCC_COVERAGE_LINK_FLAGS    "-lssl" "-lcrypto")
configure_file(crypto_unit.pc.in crypto_unit.pc @ONLY)
target_include_directories(crypto_unit PRIVATE .)
install(TARGETS crypto_unit
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)

install(FILES ${CMAKE_BINARY_DIR}/crypto_unit.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    