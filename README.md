# AUGUS CPP

> RECORD MY LEARNING

## RUN

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

### 关于全局变量/局部变量/静态变量的线程安全问题

```c++
namespace nam {
    static std::string ss;
}
```

## 一些散记

* 如果大家想看某一个领域的论文，可以尝试搜一下awesome+*，比如awesome domain adaptaion，说不定有惊喜

## 一些教程

- [ ] <a href="https://markdown.com.cn/extended-syntax/" title="扩展语法">markdown高级教程</a>
- [ ] <a href="https://markdown.com.cn/basic-syntax/" title="基本语法">markdown初级教程</a>

## BERT

- [ ] [一文读懂BERT(原理篇)](./doc/web_page/BERT-Principles.md)
- [ ] [The Illustrated Transformer](./doc/web_page/TheIllustratedTransformer.md)
- [ ] <a href="https://zhuanlan.zhihu.com/p/303080210" target="_blank"><img src="https://img.shields.io/badge/-由浅入深transformer-F08080" alt="由浅入深transformer"/> </a>
- [ ] <a href="https://zhuanlan.zhihu.com/p/68446772" target="_blank"><img src="https://img.shields.io/badge/-Bert时代的创新（应用篇）：Bert在NLP各领域的应用进展-DB7093" alt="Bert时代的创新（应用篇）：Bert在NLP各领域的应用进展"/> </a>
- [ ] <a href="https://zhuanlan.zhihu.com/p/48612853" target="_blank"><img src="https://img.shields.io/badge/-词向量之BERT-DDA0DD" alt="词向量之BERT"/> </a>

## 代码风格

[Google 开源项目风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)