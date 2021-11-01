#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

#include "gtest/gtest.h"

#define _ 0


int hhh(int &a) {
    a++;
    printf("---a---%d", a);
    return 0 ^ _ ^ 0;
    return a;
}

int jjj() {
    int a = 6;
    int answer = sizeof(hhh(a));
    auto fuc = [&](int a) { return a++; };
    printf("a##%d answer###%d", a, answer);
    return 0;
}

int a = 4;

int &f(int x) {
    a = a + x;
    return a;
}

int testMax(const int card[], int count) {
    auto pMax = std::max_element(card, card + count);
    std::cout << *pMax;
    return 0;
}


void declare() {
    int i;
    int a[100];
    for (i = 0; i < 100; i++) {
        a[i] = i;
    }
}

void print() {
    int i;
    int a[100];
    for (i = 0; i < 100; i++) {
        printf("%d ", a[i]);
    }
}


class Solution {
public:
    static int cutBar(int n, int m) {
        int slices = 1;
        int cnt = 0;
        while (slices < n) {
            ++cnt;
            slices +=  std::min(slices, m);
        }
        return cnt;
    }
};

void convolution(const double *input1, const double *input2, double *output, int mm, int nn) {
    auto *xx = new double[mm + nn - 1];
    // do convolution
    for (int i = 0; i < mm + nn - 1; i++) {
        xx[i] = 0.0;
        for (int j = 0; j < mm; j++) {
            if (i - j >= 0 && i - j < nn) {
                xx[i] += input1[j] * input2[i - j];
            }
        }
    }
    // set value to the output array
    for (int i = 0; i < mm + nn - 1; i++) {
        output[i] = xx[i];
    }
    delete[] xx;
}


int frogClimb(int m, int n, int h) {
    int day = 0;
    while (h - n > 0) { // 昨天还没爬出去
        h -= m;//白天爬了m
        ++day;
        h += n;//夜里掉了n
    }
    return day;
}

std::array<int, 6> getAverage(std::array<int, 30> arr) {
    std::array<int, 6> res{0};
    int idx = 0;
    for (int i = 0; i < arr.size();) {
        for (int j = i; j < 5; ++j) {
            res[idx] += arr[j];
        }
        ++idx;
        i += 5;
    }
    return res;
}

int getAverage() {

    int arr[30];
    for (int i = 0; i < 30; ++i) {
        arr[i] = 2 * (i + 1);
        if (i % 5 == 2) {
            printf("%d ", arr[i]);
        }
    }
//    int got[6] = {2, 7, 12, 17, 22, 27};
//    for (int i = 0; i < 6; ++i) {
//        printf("%d ", arr[got[i]]);
//    }


//    int res[6] = {0};
//    int idx = 0;
//    for (int i = 0; i < 30;) {
//        for (int j = i; j < i + 5; ++j) {
//            res[idx] += arr[j];
//        }
//        res[idx] /= 5;
//        ++idx;
//        i += 5;
//    }
//
//    for (auto i : res) {
//        std::cout << res[i] << " ";
//    }
//    std::cout << "\n";

    return 0;
}




// 3.
// 编写基类B，并派生类C。分别定义两个类的对象，针对有虚函数和无虚函数两种情况，在运行时判别并打印对象所属的类的名称：
//     （1） 基类的指针指向基类对象；
//     （2） 派生类的指针指向派生类对象；
//     （3）基类的指针指向派生类对象。

struct BasicB;
using basic_sptr = std::shared_ptr<BasicB>;

struct BasicB {
    BasicB() = default;
    ~BasicB() = default;
    virtual void fucku() { std::cout << "fuck\n"; }
    void fuck2() { std::cout << "fuck2b\n"; }
    static basic_sptr instance();
};

struct SonC;
using son_sptr = std::shared_ptr<SonC>;

struct SonC : public BasicB {
    SonC() = default;
    ~SonC() = default;
    void fucku() override { std::cout << "fuck again\n"; }
    void fuck2() { std::cout << "fuck2c\n"; }
    static son_sptr instance();
};

basic_sptr BasicB::instance() {
    static basic_sptr b_sptr = nullptr;
    if (b_sptr == nullptr) {
        b_sptr = std::make_shared<BasicB>();
    }
    return b_sptr;
}

son_sptr SonC::instance() {
    static son_sptr c_sptr = nullptr;
    if (c_sptr == nullptr) {
        c_sptr = std::make_shared<SonC>();
    }
    return c_sptr;
}


void trimMac(std::string &s) {
    int index = 0;
    if (!s.empty()) {
        while ((index = s.find('-', index)) != std::string::npos) {
            s.erase(index, 1);
        }
    }
}

int main(int argc, char *argv[]) {

    auto trimMac = [&](std::string &s) -> void {
        int index = 0;
        if (!s.empty()) {
            while ((index = s.find('-', index)) != std::string::npos) {
                s.erase(index, 1);
            }
        }
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    };

    std::string s_mac = "-AFJYGW-fawf-1-vgg3-5256-16-72---";
    std::cout<<s_mac.size()<<std::endl;
    trimMac(s_mac);
    std::cout<<s_mac.size()<<std::endl;
    std::cout<<s_mac<<std::endl;
    std::transform(s_mac.begin(), s_mac.end(), s_mac.begin(), ::toupper);
    std::cout<<s_mac<<std::endl;
    return 0;



    BasicB::instance()->fucku();

    SonC::instance()->fucku();
    auto newSon = new SonC;
    newSon->fucku();

    auto newB = new BasicB;
    newB->fuck2();
    return 0;


    char mag[8];
    std::cout << sizeof(uint32_t) << std::endl;

    getAverage();


    std::string s090 = "he sheef";
    std::cout << s090 << std::endl;
    s090 = s090.substr(s090.find(' '), *(s090.end()));
    std::cout << s090 << std::endl;


    std::cout << frogClimb(2, 1, 10) << std::endl;


    static std::default_random_engine randE(time(0));
    static std::uniform_int_distribution<uint64_t> randValue(0, 50);
    static const auto getValue = [&]() { return randValue(randE); };

    for (std::size_t i = 0; i != 3; ++i) {
        std::cout << getValue() << std::endl;
    }



    //以10分为一个分数段统计成绩
    std::vector<unsigned> scores(11, 0);
    unsigned grade;
    while (std::cin >> grade) {
        if (grade <= 100) {
            ++scores[grade / 10];
        }
    }


    return 0 ^ _ ^ 0;

    std::string s1 = "Hello World";
    std::cout << "s1 is \"Hello World\"" << std::endl;
    const std::string &s2 = s1;
    std::cout << "s2 is initialized by s1" << std::endl;
    std::string s3(s1);
    std::cout << "s3 is initialized by s1" << std::endl;
    // compare by '=='
    std::cout << "Compared by '==':" << std::endl;
    std::cout << "s1 and \"Hello World\": " << (s1 == "Hello World") << std::endl;
    std::cout << "s1 and s2: " << (s1 == s2) << std::endl;
    std::cout << "s1 and s3: " << (s1 == s3) << std::endl;
    // compare by 'compare'
    std::cout << "Compared by 'compare':" << std::endl;
    std::cout << "s1 and \"Hello World\": " << !s1.compare("Hello World") << std::endl;
    std::cout << "s1 and s2: " << !s1.compare(s2) << std::endl;
    std::cout << "s1 and s3: " << !s1.compare(s3) << std::endl;



//  return Solution::cutBar(8, 2);

    declare();
    print();


    const int CARD_DATA[54] =
            {
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,    //方块 A - K
                    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,    //梅花 A - K
                    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,    //红桃 A - K
                    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,    //黑桃 A - K
            };

    testMax(CARD_DATA, 54);


//    int t = 5;
//    cout << f(t) << endl;
//    f(t) = 20;
//    cout << f(t) << endl;
//    t = f(t);
//    cout << f(t) << endl;

    jjj();


//    char a[] = "hello";
//    a[0] = 'X';
//    char *p = "world"; // 注意p 指向常量字符串
//    p[0] = 'X'; // 编译器不能发现该错误，运行时错误

//  char a[] = "hello world";
//  char *p = a;
//  cout << sizeof(a) << endl; // 12 字节
//  cout << sizeof(p) << endl; // 4 字节
//
//  printf("\n");



    return 0;
}


