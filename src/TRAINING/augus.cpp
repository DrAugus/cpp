//
// Created by AUGUS on 2021/12/16.
//

#include "augus/augus.h"

//这不就是replace吗
void augus::AugusUtils::TrimStr(std::string &s, char str) {
    std::string::size_type index = 0;
    if (!s.empty()) {
        while ((index = s.find(str, index)) != std::string::npos) {
            s.erase(index, 1);
        }
    }
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}