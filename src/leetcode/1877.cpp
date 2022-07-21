//
// 1877.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>
#include <algorithm>

namespace leetcode {
    int minPairSum(std::vector<int> &nums) {
        std::sort(nums.begin(), nums.end());
        int res = 0;
        int len = nums.size();
        for (int i = 0; i < len / 2; ++i) {
            res = std::max(res, nums[i] + nums[len - 1 - i]);
        }
        return res;
    }
}

int main() {
    std::vector<int> v = {3, 5, 4, 2, 4, 6};
    int res = 8;
    if (leetcode::minPairSum(v) != res) return -1;

    v = {3, 5, 2, 3};
    res = 7;
    if (leetcode::minPairSum(v) != res) return -1;

    v = {4, 1, 5, 1, 2, 5, 1, 5, 5, 4};
    res = 8;
    if (leetcode::minPairSum(v) != res) return -1;

    return 1;
}
