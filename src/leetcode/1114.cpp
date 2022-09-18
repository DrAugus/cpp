//
// 1114.cpp
// Created by AUGUS on 2022/9/18.
// 按序打印
//

#include <functional>
#include <future>

class Foo {
    std::promise<void> pro1, pro2;
public:
    Foo() {

    }

    void first(std::function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        pro1.set_value();
    }

    void second(std::function<void()> printSecond) {
        pro1.get_future().wait();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        pro2.set_value();
    }

    void third(std::function<void()> printThird) {
        pro2.get_future().wait();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

int main() {
    return 1;
}