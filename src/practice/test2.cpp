//
// 2.cpp
// Created by AUGUS on 2022/5/18.
//

#include "augus.h"

// 拆分配置字符串中的数字,以","分割
bool getSectionInfo(const std::string &str, std::vector<int> &vecInt) {
    std::size_t found = str.find(",");
    std::size_t first = 0;
    while (found != std::string::npos) {
        vecInt.push_back(atoi(str.substr(first, found).c_str()));
        first = found + 1;
        found = str.find(",", first);
    }
    vecInt.push_back(atoi(str.substr(first).c_str()));
    bool res = std::all_of(vecInt.begin(), vecInt.end(), [&](int i) { return i != 0; });
    return res;
}

bool getVecString(const std::string &sectionInfo, std::vector <std::string> &vecTarget,
                  std::vector <std::vector<std::string>> &vecStr) {
    std::vector<int> vecInt;
    if (!getSectionInfo(sectionInfo, vecInt)) {
        return false;
    }
    uint32_t tend = 0;
    uint32_t num = 0;
    uint32_t tbegin = 0;

    while (num < vecInt.size() && tbegin < vecTarget.size()) {
        tend = vecInt[num];
        std::vector <std::string> tempVecStr;
        for (uint32_t i = tbegin; i < vecTarget.size() && i < tbegin + tend; ++i) {
            tempVecStr.push_back(vecTarget[i]);
        }
        vecStr.push_back(tempVecStr);
        tbegin += tend;
        ++num;
    }

    if (tbegin < vecTarget.size()) {
        std::vector <std::string> tempVecStr;
        for (uint32_t i = tbegin; i < vecTarget.size(); ++i) {
            tempVecStr.push_back(vecTarget[i]);
        }

        vecStr.push_back(tempVecStr);
    }

    return true;
}

void specifyMaskString(std::vector <std::string> &vecStr, const std::string &word) {
    const std::string &maskWord = word;
    for (auto &i: vecStr) {
        // 能短不能长
        if (i.size() < maskWord.size()) {
            continue;
        }
        i = maskWord;
    }
}

int main() {
    std::string partValue_ = "3,4";
    std::vector <std::string> singleWord = {"中", "人", "发", "阿", "放", "给", "和", "看", "后", "哦", "吗",};
    std::vector<int> vec_sec;
    if (!getSectionInfo(partValue_, vec_sec)) {
        return 0;
    }
    int index0 = vec_sec[0];
    int index1 = singleWord.size() - vec_sec[1];
    std::vector <std::string> mask_few;
    for (std::size_t i = index0; i < index1; ++i) {
        mask_few.push_back(singleWord[i]);
    }
    specifyMaskString(mask_few, "*");
    std::string trueString = "";
    std::vector <std::string> all;
    all.insert(all.end(), singleWord.begin(), singleWord.begin() + index0);
    all.insert(all.end(), mask_few.begin(), mask_few.end());
    all.insert(all.end(), singleWord.begin() + index1, singleWord.end());
    for (const auto &a: all) {
        trueString += a;
    }

    std::string ch = "中";
    std::cout << ch.size() << std::endl;


    return 1;
}

