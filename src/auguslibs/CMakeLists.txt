cmake_minimum_required(VERSION 3.9)
project(augus)

set(CXX_STANDARD_REQUIRED ON)

add_library(augus SHARED augus_libs.cpp)