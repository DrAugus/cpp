cmake参考

```cmake
cmake_minimum_required(VERSION 3.6)

project(demo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

set(INC_DIR /Users/include)

set(LINK_DIR /Users/lib)
#顺序
#step1
include_directories(${INC_DIR})
#step2
link_directories(${LINK_DIR})
#step3
link_libraries(libtest)
#step4
add_executable(demo ${SOURCE_FILES})
#step5
target_link_libraries(demo libtest)
```