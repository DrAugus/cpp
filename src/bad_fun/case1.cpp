//
// case1.cpp
// Created by AUGUS on 2022/6/16.
//

#include <iostream>

int hhh(int &a) {
    a++;
    printf("---a---%d", a);
    return a;
}

int jjj() {
    int a = 6;
    int answer = sizeof(hhh(a));
    auto fuc = [&](int a) { return a++; };
    printf("a changed? a=%d answer=%d", a, answer);
    return 0;
}

int global_a = 4;

int &f(int x) {
    global_a = global_a + x;
    return global_a;
}

int main() {
    jjj();
    std::cout << "\n" << f(2);
    std::cout << "\n" << global_a;
}