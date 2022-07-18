//
// 53.cpp
// Created by AUGUS on 2022/7/18.
// 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。
// 求所有子数组的和的最大值。
//

#include <vector>

namespace leetcode {
    int maxSubArray(std::vector<int> &nums) {
        int res = 0, max = nums[0];
        for (auto v: nums) {
            res = std::max(v + res, v);
            max = std::max(max, res);
        }
        return max;
    }
}

int main() {
    std::vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = 6;
    bool b = leetcode::maxSubArray(v) == res;
    if (b) { return 1; }
    return -1;
}