//
// 1833.cpp
// Created by AUGUS on 2022/7/18.
//

#include <vector>
#include <algorithm>

namespace leetcode {
    int maxIceCream(std::vector<int> &costs, int coins) {
        if (costs.empty()) {
            return 0;
        }
        std::sort(costs.begin(), costs.end());
        int use = 0, res = 0;
        for (auto co: costs) {
            if (co > coins) {
                //最小的都买不起
                return res;
            }
            use += co;
            ++res;
            if (use >= coins) {
                //没有那么多钱 减去最后加的
                if (use > coins) {
                    --res;
                }
                return res;
            }
        }
        return res;
    }
}

int main() {
    std::vector<int> t{1, 3, 2, 4, 1};
    if (leetcode::maxIceCream(t, 7) != 4) return -1;

    t = {10, 6, 8, 7, 7, 8};
    if (leetcode::maxIceCream(t, 5) != 0) return -1;

    t = {7, 3, 3, 6, 6, 6, 10, 5, 9, 2};
    if (leetcode::maxIceCream(t, 56) != 9) return -1;
    return 1;
}