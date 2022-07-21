//
// 172.cpp
// Created by AUGUS on 2022/7/18.
// 阶乘后的0
//

namespace leetcode {
    int trailingZeroes(int n) {
        //有多少个5就有多少个0
        int res = 0;
        int divider = 5;
        while (n / divider > 0) {
            res += n / divider;
            divider *= 5;
        }
        return res;
    }
}

int main() { return 1; }