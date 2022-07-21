//
// 448.cpp
// Created by AUGUS on 2022/7/18.
//
//

#include <vector>

namespace leetcode {
    std::vector<int> findDisappearedNumbers(std::vector<int> &nums) {
        sort(nums.begin(), nums.end());
        std::vector<int> des;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1] + 1) {
                des.push_back(nums[i - 1] + 1);
            }
        }
        return des;
    }
}

int main() { return 1; }