//
// 58.cpp
// Created by AUGUS on 2022/7/18.
// 求末尾单词的长度
//

#include <string>

namespace leetcode {
    int lengthOfLastWord(std::string s) {
        int sub_begin = -1, sub_end = s.length() - 1;
        if (s.empty() || s == " ") {
            return 0;
        }

        for (int i = s.length() - 1; i >= 0; i--) {
            if (isalpha(s[i])) {
                sub_end = i;
                break;
            }
        }
        for (int i = sub_end; i >= 0; i--) {
            if (!isalpha(s[i])) {
                sub_begin = i;
                break;
            }
        }

        return sub_end - sub_begin;
    }
}

int main() { return 1; }