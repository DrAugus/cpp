//
// 422.cpp
// Created by AUGUS on 2022/7/18.
//
//

#include <vector>

namespace leetcode {
    std::vector<int> findDuplicates(std::vector<int> &nums) {
        sort(nums.begin(), nums.end());
        std::vector<int> des;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                des.push_back(nums[i]);
                if (i != nums.size() - 1) {
                    i++;
                }
            }
        }
        return des;
    }
}

std::vector<int> findDuplicates(std::vector<int> &nums) {
    if (nums.empty()) return {};
    std::vector<int> res;
    for (auto i = 0; i < nums.size(); i++) {
        while (nums[i] != i) {
            if (nums[i] != nums[nums[i]]) {
                int temp = nums[i];
                nums[i] = nums[temp];
                nums[temp] = temp;
            } else {
                res.push_back(nums[i]);
            }
        }
    }
    return res;
}