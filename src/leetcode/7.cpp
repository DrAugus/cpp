//
// 7.cpp
// Created by AUGUS on 2022/7/18.
//

#include <climits>

namespace leetcode {
    int reverse(int x) {
        long n = 0;
        while (x) {
            n = n * 10 + x % 10;
            x /= 10;
        }
        return n > INT_MAX || n < INT_MIN ? 0 : n;
    }
}

int main() {
    if (leetcode::reverse(321) == 123 && leetcode::reverse(-132) == -231) {
        return 1;
    }
    return -1;
}