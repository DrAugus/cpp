//
// Created by AUGUS on 2022/8/8.
//

#include <iostream>
#include <string>
#include <iomanip>

int main(int argc, char **argv) {
    int i = 15;
    double d = 4.0;
    std::string s = "HackerRank ";

    std::cout << "dec like %d: " << std::dec << i << std::endl;
    std::cout << "hex like %x: " << std::hex << i << std::endl;
    std::cout << "oct like %o: " << std::oct << i << std::endl;
    std::cout << "hex like %X: " << std::setiosflags(std::ios::uppercase) << std::hex << i << std::endl;

    int i2;
    double d2;
    std::cin >> i2 >> d2;
    // 混输需要清空
    std::cin.get(); // 在输入字符串之前先用cin.get()把之前的换行符吸收掉
    std::string s2;
    getline(std::cin, s2);
    std::cout << i + i2 << std::endl;
    //setioflags(ios::fixed)   固定的浮点显示
    //setprecision(n)   设显示小数精度为n位
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(1) << d + d2 << std::endl;

    std::cout << s + s2 << std::endl;


    return 0;
}

//setfill(c) 设填充字符为c
//setw(n) 设域宽为n个字符
//setioflags(ios::scientific) 指数表示
//setiosflags(ios::left) 左对齐
//setiosflags(ios::right) 右对齐
//setiosflags(ios::skipws) 忽略前导空白
//setiosflags(ios::showpoint) 强制显示小数点
//setiosflags(ios::showpos)   强制显示符号
