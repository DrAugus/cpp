//
// Created by AUGUS on 2022/9/8.
//

#include <iostream>
#include <vector>
#include <3rd/fmt/include/fmt/core.h>


int cal_sum(int x) {
    if (!x) return 0;
    return x + cal_sum(x - 1);
}

int main() {
    fmt::print("cal sum {}\n", cal_sum(5));

    std::cout << "take it "
                 "easy?" << std::endl;

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