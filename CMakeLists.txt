#cmake 最低版本要求
cmake_minimum_required(VERSION 3.9)
#定义工程名称
project(augus_cpp
        LANGUAGES CXX
        VERSION 1.0.0
        DESCRIPTION "All my test in C++.")
#打印相关消息消息
message(status "Project Directory: ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif (MSVC)

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)
if (USE_OPENMP)
    find_package(OpenMP 3.0 COMPONENTS CXX)
    if (OpenMP_CXX_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else ()
        message(STATUS "No OpenMP found, no multithreading.")
    endif ()
endif ()

#当需要构建大型工程，各个子目录都有对应的CMakeList时，使用该条语法
add_subdirectory(src/interview)
add_subdirectory(src/practice)
add_subdirectory(src/training)
add_subdirectory(src/uv)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)

#指定编译类型 DEBUG/RELEASE
#set(cmake_build_type DEBUG)

# 指定编译器
#set(cmake_c_flags_debug "-g -Wall)

#添加编译选项
#add_compile_options(-std=gnu++11)

#设置option，可以根据option从而选择代码中的宏定义部分
#option(_LINUX "build the project on linux " ON)
#if(_LINUX)
#    add_definitions("-D_LINUX")
#endif()


#生成可执行文件
#add_executable(augus_cpp ${DIR_SRC})  #设置生成的可执行文件名字，并且把可执行文件和编译源文件关联

#生成库文件
#add_library(augus_cpp SHARED ${DIR_SRC}) #这里生成库文件有两种形式，一种是STATIC 静态库，一种是SHARED 共享库，如果需要跨硬件运行，一般是生成共享库
#add_library(augus_cpp STATIC ${DIR_SRC})
#target_link_library(augus_cpp lib1,lib2,lib3)

#指定编译包含的源文件 搜索所有的 cpp 文件
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRC) # 搜索当前目录下的所有.cpp文件
#add_library(augus_cpp ${DIR_SRC})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#要将 ADD_EXECUTABLE的声明放到设置库文件的TARGET_LINK_LIBRARIES之前



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
