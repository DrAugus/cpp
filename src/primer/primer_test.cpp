//
// Created by AUGUS on 2022/9/8.
//

#include <iostream>

int main() {
    int sum = 0, val = 50;
    while (val <= 100) {
        sum += val;
        ++val;
    }
    std::cout << sum << std::endl;
    val = -100;
    sum = 0;
    for (; val <= 100; ++val) {
        sum += val;
    }

    std::cout << sum << std::endl;

    return 0;
}