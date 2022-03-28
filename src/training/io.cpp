//
// Created by AUGUS on 2021/8/9.
//

#include "io.hh"

std::string binaryToHex(const std::string &binaryStr) {
    std::string ret;
    static const char *hex = "0123456789ABCDEF";
    for (auto c: binaryStr) {
        ret.push_back(hex[(c >> 4) & 0xf]); //取二进制高四位
        ret.push_back(hex[c & 0xf]);        //取二进制低四位
    }
    return ret;
}

void io_test::string2binary() {
    std::string sss = R"({"Account": "","FortressUser": "","AppName": "","AppPath": "","AppHash": "","Mac": "","Token": "","dport": 0,"TerminalPort": 0,"dst": "","TerminalIP": "","dbid": 0})";

    const char *json = R"({"Account": "","FortressUser": "","AppName": "","AppPath": "","AppHash": "","Mac": "","Token": "","dport": 0,"TerminalPort": 0,"dst": "","TerminalIP": "","dbid": 0})";
    std::cout << "json length: " << strlen(json) << std::endl;

    char a[164];
    strcpy(a, json);

    std::cout << "json info: ";
    for (auto ss: a) {
        std::cout << ss;
    }

    std::string changed = binaryToHex(a);

    std::cout << "\nchange to hex, now string-> ";
    for (auto ss: changed) {
        std::cout << ss;
    }
    std::cout << "\n";

    //--下面的注释已然看不懂了
    //注意修改工作路径 为 yourpath\augus_cpp\src\subpath
    std::fstream f;
    std::ifstream fin("data.txt");   //读取文件
    if (!fin) {
        std::cerr << "fail" << std::endl;
    }
    //追加写入,在原来基础上加了ios::app
    f.open("data.txt", std::ios::out | std::ios::app);
    //输入你想写入的内容
    f << "\n\n" << changed << std::endl;
    f.close();

}

int main() {
    io_test::string2binary();
}

