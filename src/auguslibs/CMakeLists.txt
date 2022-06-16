cmake_minimum_required(VERSION 3.22)
project(augus)

set(CMAKE_CXX_STANDARD 20)

add_library(augus SHARED augus_libs.cpp)