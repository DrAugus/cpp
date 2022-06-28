#cmake 最低版本要求
cmake_minimum_required(VERSION 3.9)
#定义工程名称
project(augus_cpp
        LANGUAGES C CXX
        VERSION 1.0.0
        DESCRIPTION "All my test in C++ or C.")

#打印相关消息消息
message("Project Directory: ${PROJECT_SOURCE_DIR}")
message("msg: cmake so hard")
message("Project Name: ${PROJECT_NAME}")
message("CMake Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF (WIN32)
    message("WIN32 ${PROJECT_SOURCE_DIR}")
ELSEIF (APPLE)
    message("APPLE ${PROJECT_SOURCE_DIR}")
ELSEIF (UNIX)
    message("UNIX ${PROJECT_SOURCE_DIR}")
    #设置可执行文件的输出目录
    #SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
    #分别设置了Debug版本和Release版本可执行文件的输出目录
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin)
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin)
    #设置库文件的输出目录
    #SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
    #分别设置了Debug版本和Release版本库文件的输出目录
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../lib)
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../lib)
ELSE ()
    message("OTHERS ${PROJECT_SOURCE_DIR}")
ENDIF ()

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#当需要构建大型工程，各个子目录都有对应的CMakeList时，使用该条语法
file(GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*)
foreach (add_source ${SRC})
    message("add_source: ${add_source}")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${add_source})
    add_subdirectory(${add_source})
endforeach ()

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

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)

#指定编译类型 DEBUG/RELEASE
set(cmake_build_type DEBUG)

# 指定编译器
#set(cmake_c_flags_debug "-g -Wall)

#添加编译选项
#add_compile_options(-std=gnu++11)

#设置option，可以根据option从而选择代码中的宏定义部分
option(WIN_CLION_TEST "Enable windows clion tests" OFF)

if(WIN_CLION_TEST)
    message(STATUS "Now WIN_CLION_TEST")
    add_definitions(-DWIN_CLION)
endif(WIN_CLION_TEST)

#要将 ADD_EXECUTABLE的声明放到设置库文件的TARGET_LINK_LIBRARIES之前

#生成可执行文件
add_executable(${PROJECT_NAME} augus.cpp)  #设置生成的可执行文件名字，并且把可执行文件和编译源文件关联

if (OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
endif ()

IF (WIN32)
    message(STATUS "Now is windows.")
    set(GOOGLE_LIBRARIES
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgmockd.a
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgtestd.a
            )
ELSEIF (APPLE)
    message(STATUS "Now is Apple.")
ELSEIF (UNIX)
    message(STATUS "Now is UNIX-like OS's.")
    set(GOOGLE_LIBRARIES
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgmock.a
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgtest.a
            )
ELSE ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF ()

set(AUGUS_LIBRARIES ${AUGUS_LIBRARIES} ${GOOGLE_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} ${AUGUS_LIBRARIES})

#生成库文件
#add_library(${PROJECT_NAME} SHARED ${DIR_SRC}) #这里生成库文件有两种形式，一种是STATIC 静态库，一种是SHARED 共享库，如果需要跨硬件运行，一般是生成共享库
#add_library(${PROJECT_NAME} STATIC ${DIR_SRC})
#target_link_library(${PROJECT_NAME} lib1,lib2,lib3)

#指定编译包含的源文件 搜索所有的 cpp 文件
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRC) # 搜索当前目录下的所有.cpp文件
#add_library(${PROJECT_NAME} ${DIR_SRC})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
