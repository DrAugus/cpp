# AUGUS CPP

> Recording

[notes](https://augus-docus.netlify.app/code/cpp/about)

## [RUN](./.github/workflows/cmake.yml)

1. clone `git clone https://github.com/DrAugus/cpp.git`
2. enter the dir `cd cpp`
3. make compile dir `mkdir cmake-linux-debug`
4. enter the compile dir `cd cmake-linux-debug`
5. cmake `cmake ..`
6. make `make`
7. run `./augus_cpp`

## 项目目录

* 部分子目录独立运行，参看每个子目录下的`CMakeLists`。所有`cc`/`cpp`文件带`main`函数即可独立运行

## troubleshooting

### 无法在 linux 正常编译 thread

cmake添加

```cmake
find_package (Threads REQUIRED)
target_link_libraries(${your_project_name} ${CMAKE_THREAD_LIBS_INIT})
```
