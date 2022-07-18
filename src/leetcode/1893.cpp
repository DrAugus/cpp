//
// 1893.cpp
// Created by AUGUS on 2022/7/18.
// 检查是否区域内所有整数都被覆盖
//

#include <vector>

namespace leetcode {
    bool isCovered(std::vector<std::vector<int>> &ranges, int left, int right) {
        for (int i = left; i <= right; ++i) {
            bool flag = false;
            for (auto &item: ranges) {
                if (item[0] <= i && item[1] >= i) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                return false;
            }
        }
        return true;
    }
}