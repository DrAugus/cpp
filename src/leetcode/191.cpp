//
// 191.cpp
// Created by AUGUS on 2022/7/18.
// 二进制1的个数
//

#include <bitset>

namespace leetcode {
    int hammingWeight(int n) {
        int key = n % 4;
        const int error = -1;
        // 4种算法都可行
        switch (key) {
            case 1: {
                int res = 0;
                while (n) {
                    n &= (n - 1);
                    res++;
                }
                return res;
            }
            case 2:
#ifdef __linux__
                return std::bitset<32>(n).count();
#else
                break;
#endif
            case 3:
#ifdef __linux__
                return __builtin_popcount(n);
#else
                break;
#endif
            case 4: {
                n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
                n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
                n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
                n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
                n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
                return n;
            }
            default:
                return error;
        }
        return error;
    }
}

int main() { return 1; }