//
// 168.cpp
// Created by AUGUS on 2022/7/18.
// 给定一个正整数，返回它在 Excel 表中相对应的列名称。
//

#include <string>
#include <array>

namespace leetcode {
    std::string convertToTitle(int columnNumber) {
        std::string ans;
        while (columnNumber > 0) {
            ans += --columnNumber % 26 + 'A';
            columnNumber /= 26;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
}

int main() {
    std::array<int, 4> test{1, 28, 701, 2147483647};
    std::array<std::string, 4> ans{"A", "AB", "ZY", "FXSHRXW"};
    for (int i = 0; i < 4; ++i) {
        if (leetcode::convertToTitle(test[i]) != ans[i]) {
            return -1;
        }
    }
    return 1;
}