cmake_minimum_required(VERSION 3.10)
project(utils VERSION 1.0.1 DESCRIPTION "utils")
include(GNUInstallDirs)

add_subdirectory(cryptolib)

add_subdirectory(data_transfer)
