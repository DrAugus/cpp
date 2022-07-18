//
// 13.cpp
// Created by AUGUS on 2022/7/18.
//

#include <string>
#include <unordered_map>

namespace leetcode {
    int romanToInt(std::string s) {
        std::unordered_map<char, int> symbolValues = {
                {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000},
        };
        int res = 0;
        int len = s.length();
        for (int i = 0; i < len; ++i) {
            int value = symbolValues[s[i]];
            if (i < len - 1 && value < symbolValues[s[i + 1]]) {
                res -= value;
            } else {
                res += value;
            }
        }
        return res;
    }
}