//
// 413.cpp
// Created by AUGUS on 2022/7/18.
// 等差数列划分
//

#include <vector>

namespace leetcode {
    int numberOfArithmeticSlices(std::vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() < 3) {
            return 0;
        }
        int count = 0;
        int addend = 0;

        for (int i = 2; i < nums.size(); i++) {
            if (nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1]) {
                count += ++addend;
            } else {
                addend = 0;
            }
        }
        return count;
    }
}

int main() {
    std::vector<int> t = {1, 2, 3, 4, 5};
    if(leetcode::numberOfArithmeticSlices(t) != 6) return -1;
    return 1;
}