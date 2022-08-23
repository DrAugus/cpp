//
// Created by AUGUS on 2022/8/23.
//

#include <iostream>
#include <vector>
#include <algorithm>

void reverse_dec(int a) {
    std::vector<int> res;
    while (a) {
        res.push_back(a % 10);
        a = a / 10;
    }
    for (auto i: res) {
        std::cout << i << " ";
    }
}

int reverse_bit(int a) {
    int res = 0;
    for (int i = 0; i < 6; ++i) {
        res = res << 1; // 右移
        res = res | (a & 1); // 取最右边的二进制数
        a = a >> 1; // 获取下一个
    }
    return res;
}

int main() {
    reverse_dec(29875);

    std::cout << reverse_bit(293);

    return 0;
}