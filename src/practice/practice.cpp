//
// practice.cpp
// Created by AUGUS on 2022/1/27.
//

#include "augus/augus.h"

int hhh(int &a) {
    a++;
    printf("---a---%d", a);
    return a;
}

int jjj() {
    int a = 6;
    int answer = sizeof(hhh(a));
    auto fuc = [&](int a) { return a++; };
    printf("a##%d answer###%d", a, answer);
    return 0;
}

int global_a = 4;

int &f(int x) {
    global_a = global_a + x;
    return global_a;
}

/* max_element
 * min_element
 * assign
 * reverse
 * wstring_convert
 * */

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
    static int CutBar(int n, int m) {
        int slices = 1;
        int cnt = 0;
        while (slices < n) {
            ++cnt;
            slices += std::min(slices, m);
        }
        return cnt;
    }
};

void convolution(const double *input1, const double *input2, double *output, int mm,
                 int nn) {
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

int FrogClimb(int m, int n, int h) {
    int day = 0;
    while (h - n > 0) {  // 昨天还没爬出去
        h -= m;          // 白天爬了m
        ++day;
        h += n;  // 夜里掉了n
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
    int got[6] = {2, 7, 12, 17, 22, 27};
    for (int i : got) {
        printf("%d ", arr[i]);
    }

    int res[6] = {0};
    int idx = 0;
    for (int i = 0; i < 30;) {
        for (int j = i; j < i + 5; ++j) {
            res[idx] += arr[j];
        }
        res[idx] /= 5;
        ++idx;
        i += 5;
    }

    for (auto i : res) {
        std::cout << res[i] << " ";
    }
    std::cout << "\n";

    return 0;
}

// lambda 重载 仅在c++17及以上支持
// [refer](https://stackoverflow.com/questions/58700542/overload-a-lambda-function)
constexpr auto translate = [](auto idx) {
    if constexpr (std::is_same_v<decltype(idx), int>) {
        constexpr static int table[8]{7, 6, 5, 4, 3, 2, 1, 0};
        return table[idx];
    } else if constexpr (std::is_same_v<decltype(idx), char>) {
        std::map<char, int> table{{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
                                  {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
        return table[idx];
    }
};

void WideCharacter() {
    std::string china = "中国";
    augus::PrintTest("中国", china);

    std::wstring w_china = L"中国";
    std::wcout << w_china << std::endl;

    std::wstring w_str = L"shit";
    std::string result;

    result.assign((char *)w_str.data(), w_str.size() * 2);

    std::wcout << w_str << std::endl;
    std::wcout << w_str.data() << std::endl;
    std::wcout << (char *)w_str.data() << std::endl;
    std::wcout << w_str.size() * 2 << std::endl;

    std::wcout << w_str.data() << std::endl;
    std::cout << (char *)w_str.data() << std::endl;
    std::cout << w_str.size() * 2 << std::endl;

    std::cout << result << std::endl;
}

int main() { return 0; }