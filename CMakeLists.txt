cmake_minimum_required(VERSION 2.8)
project(hash_table)

set(CMAKE_CXX_STANDARD 11)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 1)

option(HASHTABLE_LIB_MODE
    "Use to provide HASHTABLE_LIB_MODE implementation" ON)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

if (HASHTABLE_LIB_MODE)
    message("use compiler")
    add_library(HASHTABLE Prime.cpp Prime.h HashTable.hpp)
else()
    message("add executable")
    add_executable(hash_table main.cpp Prime.cpp Prime.h HashTable.hpp)
endif()
