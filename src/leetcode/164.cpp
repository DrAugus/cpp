//
// 164.cpp
// Created by AUGUS on 2022/7/18.
// Maximum Gap
//

#include <vector>

namespace leetcode {
    int maximumGap(std::vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int max_differ = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] - nums[i - 1] >= max_differ) {
                max_differ = nums[i] - nums[i - 1];
            }
        }
        return max_differ;
    }
}