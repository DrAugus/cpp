//
// Created by AUGUS on 2022/8/9.
//

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

void remove_str_space(std::string &str, char remove) {
    str.erase(std::remove(str.begin(), str.end(), remove), str.end());
}

std::array<std::string, 2> get_k_v(const std::string &str) {
    std::string tmp, l, r;
    for (auto ch: str) {
        tmp += ch;
        if (ch == '=') {
            tmp.pop_back();
            l = tmp;
            tmp = "";
            continue;
        }
    }
    r = tmp;
    return {l, r};
}

int main() {

    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::string> tag;
    for (int i = 1; i <= N / 2; ++i) {
        tag.push_back("tag" + std::to_string(i));
    }
    std::vector<std::array<std::string, 2>> val;
    for (int i = 0; i < N; ++i) {
        // record first half part
        std::string tmps;
        std::cin.get();
        getline(std::cin, tmps);

        if (i < N / 2) {
            std::string remain;
            // remove <tagx and >
            if (N / 2 > 9) remain = tmps.substr(7, tmps.size() - 8);
            else remain = tmps.substr(6, tmps.size() - 7);

            std::vector<std::string> vstemp;
            std::string catchone;
            for (auto ch: remain) {
                catchone += ch;
                bool judge = count(catchone.begin(), catchone.end(), '"') == 2 &&
                             count(catchone.begin(), catchone.end(), '=') == 1;
                if (judge) {
                    vstemp.push_back(catchone);
                    catchone = "";
                }
            }

            for (auto &iii: vstemp) {
                remove_str_space(iii, ' ');
                remove_str_space(iii, '"');
                val.push_back(get_k_v(iii));
            }
        }

    }
    return 0;
}