//
// Created by AUGUS on 2021/12/27.
//

#include "augus/augus.h"

// 3.
// 编写基类B，并派生类C。分别定义两个类的对象，针对有虚函数和无虚函数两种情况，在运行时判别并打印对象所属的类的名称：
//     （1） 基类的指针指向基类对象；
//     （2） 派生类的指针指向派生类对象；
//     （3）基类的指针指向派生类对象。

struct BasicB;
using basic_sptr = std::shared_ptr<BasicB>;

struct BasicB {
    BasicB() = default;

    ~BasicB() = default;

    virtual void fucku() { std::cout << "fuck\n"; }

    void fuck2() { std::cout << "fuck2b\n"; }

    static basic_sptr instance();
};

struct SonC;
using son_sptr = std::shared_ptr<SonC>;

struct SonC : public BasicB {
    SonC() = default;

    ~SonC() = default;

    void fucku() override { std::cout << "fuck again\n"; }

    void fuck2() { std::cout << "fuck2c\n"; }

    static son_sptr instance();
};

basic_sptr BasicB::instance() {
    static basic_sptr b_sptr = nullptr;
    if (b_sptr == nullptr) {
        b_sptr = std::make_shared<BasicB>();
    }
    return b_sptr;
}

son_sptr SonC::instance() {
    static son_sptr c_sptr = nullptr;
    if (c_sptr == nullptr) {
        c_sptr = std::make_shared<SonC>();
    }
    return c_sptr;
}

int main() {

    std::string name = "sm23.56";

    std::string time = "1920-102-2.314+213";
    std::string date = "1920/20/20+213";

    auto fn = [&](const std::string &str) {
        return str.find('-') != std::string::npos || str.find('/') != std::string::npos;
    };

    if (name.find("") != std::string::npos) {
        std::cout << "have sm\n";
        int type = std::stoi(name.substr(name.size() - 1));
        std::cout << "type" << type << "\n";
    }

    return 0;
}