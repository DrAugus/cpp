//
// augus_libs.h
// Created by AUGUS on 2022/6/16.
//

#ifndef AUGUS_CPP_AUGUS_LIBS_H
#define AUGUS_CPP_AUGUS_LIBS_H

#include <thread>
#include <memory>
#include <iostream>

#ifdef WIN32
#define AUGUS_API __declspec(dllexport)
#else
#define AUGUS_API
#endif

#ifndef _IN
#define _IN
#endif

#ifndef _OUT
#define _OUT
#endif

#ifndef _INOUT
#define _INOUT
#endif

// 命名规则 普通变量小写/下划线 类名大写所有首字母如TestName
// 类数据数据成员同普通变量如test_name但末尾要加_ 结构体数据成员同普通变量
//  https://google.github.io/styleguide/cppguide.html#Structs_vs._Classes
// 函数随意 按public首字母大写 private首词小写
// 所有类型命名 —— 类, 结构体, 类型定义 (typedef), 枚举, 类型模板参数
//   均使用相同约定, 即以大写字母开始, 每个单词首字母均大写, 不包含下划线.

namespace augus {
    class AUGUS_API GeneralInterface : std::enable_shared_from_this<GeneralInterface> {
    public:
        std::string BinaryToHex(const std::string &binaryStr);

        // inline
    public:
        bool FindTargetString(const std::string &str, const std::string &tag) {
            return str.find(tag) != std::string::npos;
        }

    public:
        GeneralInterface() = default;

        ~GeneralInterface() = default;

        GeneralInterface(const GeneralInterface &) = delete;

        GeneralInterface &operator=(GeneralInterface &) = delete;
    };
}


#endif //AUGUS_CPP_AUGUS_LIBS_H
