//
// Created by AUGUS on 2021/9/10.
//

#include <string>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"


int auto_print() {
    int H = 8, SH = 8;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < SH; ++j) {
            std::string ss = "sh-" + std::to_string(i) + "-" + std::to_string(j);
            std::string res = "<li><a href='#" + ss;
            res += "'><slot name='" + ss + "'></slot></a></li>";
            std::cout << res << std::endl;
        }
    }
    return 0;
}

TEST(auto_print, auto_print) {
    auto_print();
}



