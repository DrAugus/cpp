//
// Created by AUGUS on 2022/8/9.
//

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <unordered_map>

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

int get_num_from_str(const std::string &str) {
    std::string res;
    for (auto s: str) {
        if (s >= '0' && s <= '9') {
            res += s;
        }
    }
    if (res.empty())
        return 0;
    return std::stoi(res);
}

int main() {

    int N, Q;
    std::cin >> N >> Q;

    using tag_info = std::vector<std::array<std::string, 2>>;
    std::vector<std::unordered_map<std::string, tag_info> > val;


    for (int i = 0; i < N; ++i) {
        // record first half part
        std::string tmp_str;
        // 因上方读取了 int cin 用 get() 获取前面空白
        if (i == 0) std::cin.get();
        getline(std::cin, tmp_str);

        if (i < N / 2) {
            std::string remain, tag_str;
            // remove <tagx and > 保留空格不然会多裁剪
            if (N / 2 > 9) {
                remain = tmp_str.substr(6, tmp_str.size() - 7);
                tag_str = tmp_str.substr(1, 5);

            } else {
                remain = tmp_str.substr(5, tmp_str.size() - 6);
                tag_str = tmp_str.substr(1, 4);
            }

            std::vector<std::string> vstemp;
            std::string catch_one;
            for (auto ch: remain) {
                catch_one += ch;
                bool judge = count(catch_one.begin(), catch_one.end(), '"') == 2 &&
                             count(catch_one.begin(), catch_one.end(), '=') == 1;
                if (judge) {
                    vstemp.push_back(catch_one);
                    catch_one = "";
                }
            }

            tag_info ti;

            for (auto &iii: vstemp) {
                remove_str_space(iii, ' ');
                remove_str_space(iii, '"');
                ti.push_back(get_k_v(iii));
            }

            std::unordered_map<std::string, tag_info> single_info;
            single_info[tag_str] = ti;

            val.push_back(single_info);

        }

    }


    std::cout << "\n======= catch key value =======\n";

    for (const auto &info: val) {
        for (const auto &tt: info) {
            std::cout << tt.first << " -> ";
            for (auto kv: tt.second) {
                std::cout << kv[0] << ":" << kv[1] << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n======= catch end =======\n";


    for (int i = 0; i < Q; ++i) {
        std::string tmp_str;
        getline(std::cin, tmp_str);

        std::string catch_one;
        std::vector<std::string> vec_catch;
        for (auto ch: tmp_str) {
            if (ch == '.' || ch == '~') {
                vec_catch.push_back(catch_one);
                catch_one = "";
                continue;
            }
            catch_one += ch;
        }
        std::string value_str = tmp_str.substr(tmp_str.find('~') + 1);


        std::cout << "\n==------==\n";


        for (const auto &v: vec_catch) {
            std::cout << get_num_from_str(v) << "  ";

            std::cout << v << "  ";
        }
        std::cout << "\n";
        std::cout << value_str << "   ===";

    }

    std::cout << "\n===end===\n";

    return 0;
}