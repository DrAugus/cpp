//
// 682.cpp
// Created by AUGUS on 2022/7/18.
// 棒球比赛
//

#include <vector>
#include <string>
#include <stack>

namespace leetcode {
    int calPoints(std::vector<std::string> &ops) {
        std::stack<std::string> s;
        int res = 0;
        for (const auto &info: ops) {
            s.push(info);
            if (s.top() == "C") {
                s.pop();
                res -= std::stoi(s.top());
                s.pop();
                continue;
            }
            if (s.top() == "D") {
                s.pop();
                s.push(std::to_string(std::stoi(s.top()) * 2));
            }
            if (s.top() == "+") {
                s.pop();
                std::string second = s.top();
                s.pop();
                std::string first = s.top();
                s.pop();
                s.push(first);
                s.push(second);
                s.push(std::to_string(std::stoi(first) + std::stoi(second)));
            }
            res += std::stoi(s.top());
        }
        return res;
    }

}