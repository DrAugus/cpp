#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

#include "gtest/gtest.h"

#define _ 0

using namespace std;

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
    auto pMax = max_element(card, card + count);
    cout << *pMax;
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
            slices += min(slices, m);
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

static std::string convertTime_tToString(time_t time1)
{
    struct tm *p;
#ifdef WIN32
    p = localtime(&time1);
#else
    p = localtime(&time1);
#endif
    if (p == nullptr) {
//        LOGDYMASK_ERR("convertTime_tToString Error, Try to fix");
        size_t fixTime = 100;

        while (p == nullptr && fixTime != 0) {
            time1 = time(nullptr);
            p = localtime(&time1);
            --fixTime;
        }

        if (fixTime == 0) {
//            LOGDYMASK_ERR("convertTime_tToString fix failed");
            return "";
        }
    }

    p->tm_year = p->tm_year + 1900;
    p->tm_mon = p->tm_mon + 1;
    char szTime[1024] = { 0 };
    sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    std::stringstream sstr;
    sstr << szTime;
    return sstr.str();
}
static time_t convertStringToTime_t(const std::string& timeString)
{
    struct tm tm1;

    tm1.tm_hour = 0;
    tm1.tm_mday = 0;
    tm1.tm_min = 0;
    tm1.tm_mon = 0;
    tm1.tm_sec = 0;
    tm1.tm_wday = 0;
    tm1.tm_yday = 0;
    tm1.tm_year = 1900;

    time_t time1;

    sscanf(timeString.c_str(), "%d-%d-%d %d:%d:%d",
           &tm1.tm_year,
           &tm1.tm_mon,
           &tm1.tm_mday,
           &tm1.tm_hour,
           &tm1.tm_min,
           &tm1.tm_sec
    );

    tm1.tm_year -= 1900;
    --tm1.tm_mon;
    tm1.tm_isdst = -1;
    time1 = mktime(&tm1);
    return time1;
}

int main(int argc, char *argv[]) {



    std::string trueString = "1899-11-22 22:29:36";

    uint32_t timeSeed = time(nullptr);

    time_t tm = convertStringToTime_t(trueString);

    time_t daySec = 24 * 3600;

    std::default_random_engine rander;
    rander.seed(timeSeed);

        std::uniform_int_distribution<time_t> randTime(-daySec, daySec);
        tm += randTime(rander);

    trueString = convertTime_tToString(tm);

    auto newss =trueString.substr(trueString.find(' ')+1);



    std::cout << newss << std::endl;






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

    string s1 = "Hello World";
    cout << "s1 is \"Hello World\"" << endl;
    const string &s2 = s1;
    cout << "s2 is initialized by s1" << endl;
    string s3(s1);
    cout << "s3 is initialized by s1" << endl;
    // compare by '=='
    cout << "Compared by '==':" << endl;
    cout << "s1 and \"Hello World\": " << (s1 == "Hello World") << endl;
    cout << "s1 and s2: " << (s1 == s2) << endl;
    cout << "s1 and s3: " << (s1 == s3) << endl;
    // compare by 'compare'
    cout << "Compared by 'compare':" << endl;
    cout << "s1 and \"Hello World\": " << !s1.compare("Hello World") << endl;
    cout << "s1 and s2: " << !s1.compare(s2) << endl;
    cout << "s1 and s3: " << !s1.compare(s3) << endl;



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


    int t = 5;
    cout << f(t) << endl;
    f(t) = 20;
    cout << f(t) << endl;
    t = f(t);
    cout << f(t) << endl;

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


