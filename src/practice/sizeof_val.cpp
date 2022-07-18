//
// sizeof_val.cpp
// Created by AUGUS on 2022/7/18.
//

#include <iostream>

int main() {
    std::cout << "sizeof test\n";

    std::cout << "sizeof string " << sizeof(std::string) << std::endl;
    std::cout << "sizeof long double " << sizeof(long double) << std::endl;
    std::cout << "sizeof double " << sizeof(double) << std::endl;
    std::cout << "sizeof size_t " << sizeof(size_t) << std::endl;
    std::cout << "sizeof float " << sizeof(float) << std::endl;
    std::cout << "sizeof unsigned " << sizeof(unsigned) << std::endl;
    std::cout << "sizeof short " << sizeof(short) << std::endl;
    std::cout << "sizeof wchar_t " << sizeof(wchar_t) << std::endl;

    std::cout << "sizeof long long " << sizeof(long long) << std::endl;
    std::cout << "sizeof long " << sizeof(long) << std::endl;
    std::cout << "sizeof int " << sizeof(int) << std::endl;
    std::cout << "sizeof bool " << sizeof(bool) << std::endl;
    std::cout << "sizeof char " << sizeof(char) << std::endl;

    std::cout << "sizeof unsigned long long " << sizeof(unsigned long long) << std::endl;
    std::cout << "sizeof unsigned long " << sizeof(unsigned long) << std::endl;
    std::cout << "sizeof unsigned int " << sizeof(unsigned int) << std::endl;
    std::cout << "sizeof unsigned char " << sizeof(unsigned char) << std::endl;

    auto f_lam = [](int a) -> int { return a + 1; };
    std::cout << "sizeof f_lam " << sizeof(f_lam) << std::endl;
    return 0;
}