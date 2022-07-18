//
// 1.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>
#include <unordered_map>

namespace leetcode {
    std::vector<int> twoSum(std::vector<int> &nums, int target){
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end()) {
                return {iter->second, i};
            }
            map.insert(std::pair<int, int>(nums[i], i));
        }
        return {};
    }
}

int main() {
    std::vector<int> nums = {3,2,4};
    int target = 6;
    std::vector<int> res = {1, 2};
    if (res == leetcode::twoSum(nums, target)) {
        return 1;
    }
    return -1;
}