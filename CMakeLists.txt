cmake_minimum_required(VERSION 2.8)
project(hash_table)

set(CMAKE_CXX_STANDARD 11)

add_executable(hash_table main.cpp Prime.cpp Prime.h HashTable.cpp HashTable.h)
