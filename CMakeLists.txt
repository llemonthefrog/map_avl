cmake_minimum_required(VERSION 3.10)

project(AvlMap)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(avlmap STATIC src/avlmap.cpp)

target_include_directories(avlmap PUBLIC include)