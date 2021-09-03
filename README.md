# augus_cpp

JUST TEST

RECORD MY LEARNING

## 项目目录

* 所有子目录独立运行，参看每个子目录下的`CMakeLists`。所有`cc`文件带`main`函数即可独立运行

<h1>troubleshooting</h1>

<h2>clion同时配置Makefile和Cmakelist如何让Cmakelist生效？</h2>
似乎修改Run/Debug Configurations即可<br>如若不行移除项目的makefile让cmakelist先生效<br>

<h2>关于全局变量/局部变量/静态变量的线程安全问题</h2>
```c++
namespace nam {
    static std::string ss;
}
```


# Notes


### 1、需要某元素总个数时，使用count

对于只需要知道包含特定元素的数量的应用来说，这是最简单的方式。如果count返回0，则表示不存在该元素。

```C++
if (count(v.begin(), v.end(), key))
```

### 2、仅判断是否存在某元素，使用find

find会在查找到指定值后立即返回，所以它一般比count更快（因为count总是要遍历整个容器）。

```C++
if (std::find(v.begin(), v.end(), key) != v.end())
```

### 3、支持复杂条件的查找时，使用any_of(仅知道是否存在)/find_if(返回了第一个元素的迭代器)

#### std::find_if

它也能完成任务，但有点大材小用了。

find_if需要一个判别式。如果查找的值需要满足特定的条件时，比如查找小于3且大于1的值时，适合该方式。

如果有多个值符合条件，则返回查找到符合条件的第一个值的迭代器。

```C++
if (std::find_if(v.begin(), v.end(), [] (int i) { return i < 3 && i > 1 } ) != v.end())
```

#### std::any_of

与find_if类似，但它返回bool值。

如果判断式返回true，则它也返回true。否则返回false。

```C++
if (std::any_of(v.begin(), v.end(), [] (int i) { return i < 3 && i > 1 } ))
```

扩展：std::none_of，是any_of的反面。也就是，当判断式是false时它返回true，否则返回flase。

### 4、对于已经排序的vector，使用binary_search

作为磨刀不误砍柴工的一种方式，可以对vector先排序，再查找，就可以使用二分查找了。

二分查找的时间效率为O(logn)。

```C++
sort(v.begin(), v.end());
if (std::binary_search(v.begin(), v.end(), key))
```

