//
// 421.cpp
// Created by AUGUS on 2022/7/18.
// 数组中两个数的最大异或值
//

#include <vector>
#include <algorithm>

namespace leetcode {
    int findMaximumXOR(std::vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        auto biggest = std::max_element(begin(nums), end(nums));
        int res = 0;
        for (auto compare: nums) {
            int max = compare ^ *biggest;
            if (max > res) {
                res = max;
            }
            //    res = (compare ^ *biggest) > res ? (compare ^ *biggest) : res;
        }
        return res;
    }
}

int main() { return 1; }