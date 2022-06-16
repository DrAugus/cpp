//
// augus_libs.cpp
// Created by AUGUS on 2022/6/16.
//

#include "augus_libs.h"

using namespace augus;

std::string GeneralInterface::BinaryToHex(const std::string &binaryStr) {
    std::string ret;
    static const char *hex = "0123456789ABCDEF";
    for (auto c: binaryStr) {
        ret.push_back(hex[(c >> 4) & 0xf]); //取二进制高四位
        ret.push_back(hex[c & 0xf]);        //取二进制低四位
    }
    return ret;
}
