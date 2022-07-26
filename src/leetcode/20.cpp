//
// 20.cpp
// Created by AUGUS on 2022/7/26.
// 括号匹配
//

#include <string>
#include <stack>

namespace leetcode {
    bool isValid(std::string s) {
        std::stack<char> stack;
        std::string bracketLeft = "{[(";
        std::string bracketRight = "}])";
        for (char chr : s) {
            int indexLeft = -1, indexRight = -1;
            indexLeft = bracketLeft.find(chr);
            indexRight = bracketRight.find(chr);
            // 是左括号
            if (indexLeft >= 0) {
                stack.push(chr);  // 入栈
                // 是右括号
            } else if (indexRight >= 0) {
                // 匹配成功
                if (!stack.empty() && stack.top() == bracketLeft[indexRight]) {
                    stack.pop();  // 出栈
                } else {
                    return false;
                }
            }
        }
        return stack.empty();
    }
}

int main() {
    return 1;
}