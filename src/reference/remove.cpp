//
// remove.cpp
// Created by AUGUS on 2022/6/28.
//
#include <algorithm>
#include <string>
#include <string_view>
#include <iostream>
#include <cctype>
#include <vector>

bool isOdd(int i) { return i & 2; }

void print(const std::vector<int> &v) {
    for (const auto &i: v) { std::cout << i << ' '; }
    std::cout << '\n';
}

void example() {

    // Initializes a vector that holds numbers from 0-9.
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(v);

    // Removes all elements with the value 5.
    v.erase(std::remove(v.begin(), v.end(), 5), v.end());
    print(v);

    // Removes all odd numbers.
    v.erase(std::remove_if(v.begin(), v.end(), isOdd), v.end());
    print(v);
}

int main() {
    std::string str1 = "Text with some   spaces";

    std::cout << "str1 size: " << str1.size() << std::endl;

    auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

    //TODO
#ifdef _WIN32
    // The spaces are removed from the string only logically.
    // Note, we use view, the original string is still not shrunk:
    std::cout << std::string_view(str1.begin(), noSpaceEnd)
              << " size: " << str1.size() << '\n';

    str1.erase(noSpaceEnd, str1.end());
#endif

    // The spaces are removed from the string physically.
    std::cout << str1 << " size: " << str1.size() << '\n';

    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(),
                              str2.end(),
                              [](unsigned char x) { return std::isspace(x); }),
               str2.end());
    std::cout << str2 << '\n';

    std::cout << "example" << '\n';
    example();

    return 0;
}