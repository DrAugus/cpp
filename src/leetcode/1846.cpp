//
// 1846.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>
#include <algorithm>

namespace leetcode {
    int maximumElementAfterDecrementingAndRearranging(std::vector<int> &arr) {
        if (arr.empty()) {
            return 0;
        }
        std::sort(arr.begin(), arr.end());
        if (arr[0] != 1) {
            arr[0] = 1;
        }
        for (int i = 1; i < arr.size(); ++i) {
            int val = arr[i - 1] - arr[i];
            int a = val > 0 ? val : (-val);
            if (val > 1) {
                arr[i - 1] -= (a - 1);
            }
            if (val < -1) {
                arr[i] -= (a - 1);
            }
        }
        return arr[arr.size() - 1];
    }
}

int main() { return 1; }