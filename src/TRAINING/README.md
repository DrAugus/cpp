# TRAINNING

所有 `LeetCode` `CodeWars` 刷题记录


### ERROR

`findMedianSortedArrays`调用`for_training`里`mergeTest`方法链接失败

* 诱发原因： 两个文件目录里均链接了gtest动态库，在相互调用时 链接出错
* 解决办法： 文件移动至同目录

```
CMakeFiles\TRAINING.dir/objects.a(main.cc.obj): In function `main':
D:/Users/dell/CLionProjects/augus_cpp/src/TRAINING/main.cc:15: undefined reference to `whywhywhy()'
collect2.exe: error: ld returned 1 exit status
mingw32-make.exe[3]: *** [src\TRAINING\CMakeFiles\TRAINING.dir\build.make:121: src/TRAINING/TRAINING.exe] Error 1
mingw32-make.exe[2]: *** [CMakeFiles\Makefile2:412: src/TRAINING/CMakeFiles/TRAINING.dir/all] Error 2
mingw32-make.exe[1]: *** [CMakeFiles\Makefile2:419: src/TRAINING/CMakeFiles/TRAINING.dir/rule] Error 2
mingw32-make.exe: *** [Makefile:295: TRAINING] Error 2
```