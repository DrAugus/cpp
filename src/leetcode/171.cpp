//
// 171.cpp
// Created by AUGUS on 2022/7/18.
// 给定一个Excel表格中的列名称，返回其相应的列序号。
//

#include <string>
#include <array>

namespace leetcode {
    int titleToNumber(std::string columnTitle) {
        //    int res = 0;
        //    int mul = 1;
        //    for (int i = columnTitle.size() - 1; i >= 0; --i) {
        //        int k = (columnTitle[i] - 'A' + 1);
        //        res += k * mul;
        //        mul *= 26;
        //    }
        //    return res;

        // above越界

        int n = columnTitle.length() - 1;
        int res = 0;
        for (int i = 0; i <= n; i++) {
            res = columnTitle.at(i) - 'A' + 1 + 26 * res;
        }
        return res;
    }
}


int main() {
    std::array<int, 4> test{1, 28, 701, 2147483647};
    std::array<std::string, 4> ans{"A", "AB", "ZY", "FXSHRXW"};
    for (int i = 0; i < 4; ++i) {
        if (leetcode::titleToNumber(ans[i]) != test[i]) {
            return -1;
        }
    }
    return 1;
}