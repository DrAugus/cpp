//
// 34.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>

namespace leetcode {
    std::vector<int> searchRange(std::vector<int> &nums, int target) {
        std::vector<int> res(2, -1);
        if (nums.empty()) {
            return res;
        }
        int len = nums.size();
        int left = 0;
        int right = len - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            }
        }
        if (nums[left] != target) {
            return res;
        }
        res[0] = left;
        right = len;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid;
            }
        }
        res[1] = right - 1;
        return res;
    }
}

int main() {
    std::vector<int> v = {5, 7, 7, 8, 8, 10};
    int t = 6;
    std::vector<int> res = {-1, -1};
    bool expect;
    expect = leetcode::searchRange(v, t) == res;
    if (!expect) { return -1; }
    v = {2, 2};
    t = 2;
    res = {0, 1};
    expect = leetcode::searchRange(v, t) == res;
    if (!expect) { return -1; }
    return 1;
}