//
// 45.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>

namespace leetcode {
    int jump(std::vector<int> &nums) {
        if (nums[0] == 0) {
            return 0;
        }

        int LastIndex = nums.size() - 1;
        if (LastIndex <= 1) {
            return LastIndex;
        }

        for (int i = 0; i <= LastIndex; i++) {
            if (nums[i] == 0) {
                continue;
            }
            if (nums[i] + i >= LastIndex) {
                if (i == 0) {
                    return 1;
                } else {
                    for (int j = nums.size() - 1; j > i; j--) {
                        nums.pop_back();
                    }
                    return 1 + jump(nums);
                }
            }
        }

        return 0;
    }
}

int main() { return 1; }