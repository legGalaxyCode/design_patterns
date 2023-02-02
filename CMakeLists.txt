cmake_minimum_required(VERSION 3.24)
project(design_patterns)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(behavioral)
add_subdirectory(creational)
add_subdirectory(structural)

add_executable(design_patterns main.cpp)
