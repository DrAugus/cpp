//
// 239.cpp
// Created by AUGUS on 2022/7/18.
// Sliding Window Maximum
//

#include <vector>
#include <deque>

namespace leetcode {
    std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
        std::vector<int> res;
        std::deque<int> q;
        for (int i = 0; i < nums.size(); ++i) {
            if (!q.empty() && q.front() == i - k) {
                q.pop_front();
            }
            while (!q.empty() && nums[q.back()] < nums[i]) {
                q.pop_back();
            }
            q.push_back(i);
            if (i >= k - 1) {
                res.push_back(nums[q.front()]);
            }
        }

        return res;
    }
}

// 低级实现
std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
    std::vector<int> res;
    if (k >= nums.size()) {
        res.push_back(*max_element(nums.begin(), nums.end()));
        return res;
    }

    int begin = 0;
    std::vector<std::vector<int>> des(nums.size() - k + 1);
    for (int i = 0; i <= nums.size() - k; i++) {
        for (int j = begin; j < begin + k; j++) {
            des[i].push_back(nums[j]);
        }
        begin++;
    }

    for (int i = 0; i <= nums.size() - k; i++) {
        res.push_back(*max_element(des[i].begin(), des[i].end()));
    }

    return res;
}
