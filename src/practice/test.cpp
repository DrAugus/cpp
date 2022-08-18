//
// Created by AUGUS on 2022/8/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <unordered_set>

void plusMinus(std::vector<int> arr) {
    if (arr.empty()) return;
    int len = arr.size();
    int pos = 0, neg = 0, zero = 0;
    for (auto i: arr) {
        if (i > 0) ++pos;
        else if (i == 0) ++zero;
        else ++neg;
    }
    double a = (double) pos / len, b = (double) neg / len, c = (double) zero / len;
    printf("%.6f\n%.6f\n%.6f\n", a, b, c);
}

int updatePointer(int *a, int *b) {
    int ta = *a, tb = *b;
    *a = ta + tb;
    *b = ta - tb;
    return 0;
}

int mainPointer() {
    int a, b;
    int *pa = &a, *pb = &b;

    scanf("%d %d", &a, &b);
    updatePointer(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}

int repeat_ele(const std::vector<int> &a) {
    std::unordered_set<int> s;
    for (int i: a) {
        if (s.find(i) != s.end()) {
            return i;
        }
        s.insert(i);
    }
    return 0;
}

int lonely_integer(std::vector<int> a) {
    int res = 0;
    for (int i: a) {
        res ^= i;
    }
    return res;
}


//11 2 4
//4 5 6
//10 8 -12
// 11 + 5 - 12 = 4
// 4 + 5 + 10 = 19
// |4 - 19| = 15
int diagonalDifference(std::vector<std::vector<int>> arr) {
    int len = arr.size();
    int sum1 = 0, sum2 = 0;
    for (int i = 0, j = len - 1; i < len; ++i, --j) {
        sum1 += arr[i][j];
        sum2 += arr[i][i];
    }
    return abs(sum2 - sum1);
}

int main() {

    std::vector<int> iii = {1, 2, 3, 4, 4, 3, 2, 1, 5, 6, 5};
    std::cout << lonely_integer(iii);


    mainPointer();

    printf("=================\n");

    std::vector<int> a = {-4, 3, -9, 0, 4, 1};
    std::sort(a.begin(), a.end());

    plusMinus(a);

    std::string ss = "123456x";
    std::cout << ss.substr(3, 2) << std::endl;


    std::cout << stoi(ss, nullptr);


}