//
// 2028.cpp
// Created by AUGUS on 2022/7/18.
// 找出缺失的观测数据
//

#include <vector>
#include <numeric>
#include <algorithm>

namespace leetcode {
    std::vector<int> missingRolls(std::vector<int> &rolls, int mean, int n) {
        int sum = mean * (rolls.size() + n) - std::accumulate(rolls.begin(), rolls.end(), 0);
        if (sum > 6 * n || sum < n) {
            return {};
        }
        int v = sum / n;
        std::vector<int> res(n, v);
        if (v == 6)
            return res;
        sum -= v * n;
        for (int i = 0; sum; ++i) {
            int add = std::min(sum, 6 - v);
            res[i] += add;
            sum -= add;
        }
        return res;
    }
}

int main() {
    std::vector<int> eq;
    std::vector<int> v = {1, 5, 6};
    int mean = 3;
    int n = 4;
    std::vector<int> result = {};
    result = leetcode::missingRolls(v, mean, n);
    eq = {3, 2, 2, 2};
    if (eq != result) return -1;

    v = {3, 5, 3};
    mean = 5;
    n = 3;
    result = leetcode::missingRolls(v, mean, n);
    eq = {};
    if (eq != result) return -1;

    return 1;
}