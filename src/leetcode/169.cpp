//
// 169.cpp
// Created by AUGUS on 2022/9/17.
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
//

#include <algorithm>
#include <vector>
#include <unordered_map>

namespace leetcode {
    int majorityElement(std::vector<int> &nums) {
        std::unordered_map<int, int> um;
        int majority = 0, count = 0;
        for (int n: nums) {
            ++um[n];
            if (um[n] > count) {
                majority = n;
                count = um[n];
            }
        }
        return majority;
    }
}

int main() {
    std::vector<int> nums = {3, 2, 3};
    bool res;
    res = leetcode::majorityElement(nums) == 3;
    nums = {2, 2, 1, 1, 1, 2, 2};
    res &= leetcode::majorityElement(nums) == 2;
    if (res)
        return 1;
    return -1;
}