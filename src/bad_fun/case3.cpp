//
// case3.cpp
// Created by AUGUS on 2022/6/16.
//

#include<iostream>

int main(int argc, char *argv[]) {
    std::string china = "中国";
    std::cout << china << std::endl;

    std::wstring w_china = L"中国";
    std::wcout << w_china << std::endl;

    std::wstring w_str = L"shit";
    std::string result;

    result.assign((char *) w_str.data(), w_str.size() * 2);

    std::wcout << w_str << std::endl;
    std::wcout << w_str.data() << std::endl;
    std::wcout << (char *) w_str.data() << std::endl;
    std::wcout << w_str.size() * 2 << std::endl;

    std::wcout << w_str.data() << std::endl;
    std::cout << (char *) w_str.data() << std::endl;
    std::cout << w_str.size() * 2 << std::endl;

    std::cout << result << std::endl;

    return 0;
}