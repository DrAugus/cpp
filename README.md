# augus_cpp

JUST TEST

RECORD MY LEARNING

显而易见 GitHub自带的code分析 不支持分析带有gtest的项目

## 项目目录

* 所有子目录独立运行，参看每个子目录下的`CMakeLists`。所有`cc`文件带`main`函数即可独立运行

# troubleshooting

## clion同时配置Makefile和Cmakelist如何让Cmakelist生效？

似乎修改Run/Debug Configurations即可<br>如若不行移除项目的makefile让cmakelist先生效<br>

## 关于全局变量/局部变量/静态变量的线程安全问题

```c++
namespace nam {
    static std::string ss;
}
```

