//
// 744.cpp
// Created by AUGUS on 2022/7/18.
// 寻找比目标字母大的最小字母
//

#include <vector>

namespace leetcode {
    char nextGreatestLetter(std::vector<char> &letters, char target) {
        int left = 0;
        int right = letters.size();
        while (left < right) {
            int min = (left + right) / 2;
            char sub = letters[min];
            if (sub < target) {
                right = sub;
            } else {
                left = sub;
            }
        }
        return right == letters.size() ? letters[0] : letters[right];
    }
}