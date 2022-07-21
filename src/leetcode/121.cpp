//
// 121.cpp
// Created by AUGUS on 2022/7/18.
// 买卖股票的最佳时机  Best Time to Buy and Sell Stock IV
//

#include <vector>
#include <algorithm>

namespace leetcode {
    int maxProfit(int k, std::vector<int> &prices) {
        if (prices.empty() || prices.size() == 1) {
            return 0;
        }

        std::vector<int> resGoal(k - 1);

        std::vector<int> resDiff;
        resDiff.reserve(prices.size() - 1);
        for (auto i = 0; i < prices.size() - 1; i++) {
            for (auto j = i + 1; j < prices.size(); j++) {
                resDiff.push_back(prices[j] - prices[i]);
            }
        }
        std::sort(resDiff.rbegin(), resDiff.rend());
        int res = 0;
        for (int i = 0; i < k; i++) {
            int tempRes = res;
            res += resDiff[i];
            if (res < tempRes) {
                res -= resDiff[i];
            }
        }
        return res;
    }
}

int main() { return 1; }