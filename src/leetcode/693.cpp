//
// 693.cpp
// Created by AUGUS on 2022/7/18.
// 交替位二进制数
// 移位异或后就全为1了，然后做的就是判断 A&A+1是否为零，为零为交替位，反之非交替位
//

namespace leetcode {
    bool hasAlternatingBits(int n) {
        int a = n >> 1 ^ n;
        return !(a & a + 1);
    }
}