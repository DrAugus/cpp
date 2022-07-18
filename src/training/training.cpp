//
// Created by Augus on 2020/6/6.
//

#include "training.hh"

using namespace leetcode;
using namespace codewars;

LCSolution_sptr LCSolution::instance() {
    static LCSolution_sptr sptr = nullptr;
    if (sptr == nullptr) {
        sptr = std::make_shared<LCSolution>();
    }
    return sptr;
}

std::vector<std::vector<int>> LCSolution::prefixSum(std::vector<std::vector<int>> a) {
    std::vector<std::vector<int>> b;
    int n = a.size();     // n行
    int m = a[0].size();  // m列
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (x == 0 && y == 0) {
                b[y][x] = a[y][x];  //左上角的值
            } else if (x == 0) {
                b[y][x] = b[y - 1][x] + a[y][x];  //第一列
            } else if (y == 0) {
                b[y][x] = b[y][x - 1] + a[y][x];  //第一行
            } else {
                b[y][x] = b[y - 1][x] + b[y][x - 1] - b[y - 1][x - 1] + a[y][x];
            }
        }
    }
    return b;
}

int codewars::CWSolution::Multiples3Or5(int number) {
    const int err = -1;
    const int kind_sol = 2;
    switch (number % kind_sol) {
        case 1: {
            /// < number
            /// 商
            int a1 = number / 3, a2 = number / 5, a3 = number / 15;
            /// 余数
            int b1 = number % 3, b2 = number % 5, b3 = number % 15;
            /// 3、5、15的倍数的数目
            int c1 = 0, c2 = 0, c3 = 0;
            /// < number
            if (!b1) {
                a1 -= 1;
            }
            if (!b2) {
                a2 -= 1;
            }
            if (!b3) {
                a3 -= 1;
            }

            for (int i = 1; i <= a1; i++) {
                c1 += i;
            }
            for (int i = 1; i <= a2; i++) {
                c2 += i;
            }
            for (int i = 1; i <= a3; i++) {
                c3 += i;
            }
            return c1 * 3 + c2 * 5 - c3 * 15;
        }
        case 2: {
            int sum = 0;
            for (int n = 3; n < number; n++) {
                if ((n % 3 == 0) || (n % 5 == 0)) {
                    sum += n;
                }
            }
            return sum;
        }
        default:
            return err;
    }
    return err;
}

bool codewars::CWSolution::validBraces(std::string braces) {
    std::random_device rd;
    int number = rd();
    const int kind_sol = 2;
    switch (number % kind_sol) {
        case 1: {
            /// Others Written
            /// learning stack
            std::stack<char> s;
            std::string bracketLeft = "{[(";
            std::string bracketRight = "}])";
            for (char chr : braces) {
                int indexLeft = -1, indexRight = -1;
                indexLeft = bracketLeft.find(chr);
                indexRight = bracketRight.find(chr);
                // 是左括号
                if (indexLeft >= 0) {
                    s.push(chr);  // 入栈
                    // 是右括号
                } else if (indexRight >= 0) {
                    // 匹配成功
                    if (!s.empty() && s.top() == bracketLeft[indexRight]) {
                        s.pop();  // 出栈
                    } else {
                        return false;
                    }
                }
            }
            return s.empty();
        }
        case 2: {
            std::regex r(R"(\(\)|\[\]|\{\})");
            while (regex_search(braces, r)) {
                braces = regex_replace(braces, r, "");
            }
            return braces.length() == 0;
        }
        default:
            return false;
    }
}

int codewars::SnailSort::GetDirection(bool Direction[4]) {
    for (int i = 0; i < 4; i++) {
        if (Direction[i]) {
            return i;
        }
    }
    return 0;
}

bool codewars::SnailSort::IsArrived(int CurrentPosX, int CurrentPosY, int FinalPosX, int FinalPosY) {
    return CurrentPosX == FinalPosX && CurrentPosY == FinalPosY;
}

std::vector<int> codewars::SnailSort::snail(const std::vector<std::vector<int>> &snail_map, bool isOthers) {
    if (snail_map.size() <= 1) {
        return snail_map[0];
    }

    std::vector<int> Res;
    int FinalPosX = 0;
    int FinalPosY = 0;
    if (snail_map.size() % 2 == 0) {
        FinalPosX = snail_map.size() - snail_map.size() / 2;
        FinalPosY = snail_map.size() / 2 - 1;
    } else {
        FinalPosX = snail_map.size() / 2;
        FinalPosY = snail_map.size() / 2;
    }

    int CurrentPosX = 0;
    int CurrentPosY = 0;

    int RightFrame = snail_map[0].size() - 1;
    int DownFrame = snail_map.size() - 1;
    int LeftFrame = 0;
    int UpFrame = 0;

    bool DirectionGo[4] = {true, false, false, false};
    while (CurrentPosX != FinalPosX || CurrentPosY != FinalPosY) {
        switch (GetDirection(DirectionGo)) {
            case RIGHT:

                CurrentPosX = UpFrame;
                for (int StartPos = LeftFrame; StartPos <= RightFrame; StartPos++) {
                    Res.push_back(snail_map[UpFrame][StartPos]);
                    CurrentPosY = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                UpFrame++;

                DirectionGo[RIGHT] = false;
                DirectionGo[(RIGHT + 1) % 4] = true;
                break;
            case DOWN:

                CurrentPosY = RightFrame;
                for (int StartPos = UpFrame; StartPos <= DownFrame; StartPos++) {
                    Res.push_back(snail_map[StartPos][RightFrame]);
                    CurrentPosX = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                RightFrame--;

                DirectionGo[DOWN] = false;
                DirectionGo[(DOWN + 1) % 4] = true;
                break;
            case LEFT:

                CurrentPosX = DownFrame;
                for (int StartPos = RightFrame; StartPos >= LeftFrame; StartPos--) {
                    Res.push_back(snail_map[DownFrame][StartPos]);
                    CurrentPosY = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                DownFrame--;

                DirectionGo[LEFT] = false;
                DirectionGo[(LEFT + 1) % 4] = true;
                break;
            case UP:

                CurrentPosY = LeftFrame;
                for (int StartPos = DownFrame; StartPos >= UpFrame; StartPos--) {
                    Res.push_back(snail_map[StartPos][LeftFrame]);
                    CurrentPosX = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                LeftFrame++;

                DirectionGo[UP] = false;
                DirectionGo[(UP + 1) % 4] = true;
                break;
        }
    }
    return Res;
}

std::vector<int> codewars::SnailSort::snail(const std::vector<std::vector<int>> &snail_map) {
    ///// GOT CycleTimes
    //// 5x5
    //// 5 4 4 3
    //// 3 2 2 1
    //// 1

    //// 6x6
    //// 6 5 5 4
    //// 4 3 3 2
    //// 2 1 1

    //// 7x7
    //// 7 6 6 5
    //// 5 4 4 3
    //// 3 2 2 1
    //// 1

    if (snail_map.empty()) {
        return {};
    }

    std::vector<int> res;

    if (snail_map.size() == 1) {
        //    res.push_back(snail_map[0][0]); /// 内存泄漏
        res = snail_map[0];
        return res;
    }

    //// n x n
    const int rank = snail_map.size();

    int begin = 0, end = rank;

    int CycleTimes = ((rank * 2) - 1) / 4;
    if (((rank * 2) - 1) % 4) {
        //// CycleTimes 矫正
        CycleTimes++;
    }

    while (CycleTimes) {
        //////正向 横竖
        for (int i = begin; i < end; i++) {
            res.push_back(snail_map[begin][i]);
        }
        for (int i = begin + 1; i < end; i++) {
            res.push_back(snail_map[i][end - 1]);
        }
        //////反向 横竖
        for (int i = end - 2; i >= begin; i--) {
            res.push_back(snail_map[end - 1][i]);
        }
        for (int i = end - 2; i >= begin + 1; i--) {
            res.push_back(snail_map[i][begin]);
        }
        begin++;
        end--;

        CycleTimes--;
    }

    return res;
}

int codewars::Casino::ColorCount(std::vector<int> v) {
    int Count = 0;
    for (int i = 0; i < 3; i++) {
        if (v[i] > 0) {
            Count++;
        }
    }
    return Count++;
}

int codewars::Casino::solution(std::vector<int> v) {
    int DayCount = 0;
    bool HaveColor[3] = {v[0] > 0, v[1] > 0, v[2] > 0};

    while (ColorCount(v) >= 2) {
        bool bTaken[3] = {false, false, false};
        for (int j = 0; j < 2; j++) {
            int TempColorMaxCount = 0;
            int TempColor = 0;
            for (int i = 0; i < 3; i++) {
                if (!bTaken[i] && HaveColor[i] && v[i] >= TempColorMaxCount) {
                    TempColor = i;
                    TempColorMaxCount = v[i];
                }
            }
            v[TempColor]--;
            bTaken[TempColor] = true;
            HaveColor[TempColor] = v[TempColor] > 0;
        }
        DayCount++;
    }

    return DayCount;
}

//TEST(codewars_t1, Casino) {
//    auto p = new codewars::Casino;
//    EXPECT_EQ(p->solution({1, 1, 1}),
//              1);  // because after you pick on day one, there will be only one chip left
//    EXPECT_EQ(p->solution({1, 2, 1}),
//              2);  // you can pick twice; you pick two chips on day one then on day two
//    EXPECT_EQ(p->solution({4, 1, 1}), 2);
//}

int Palindrome::maxSlidingWindow(const std::vector<int> &nums, int k, int MaxValue, std::vector<int> &AllNum) {
    int Count = 0;

    int EndPos = k;
    for (int StartPos = 0; EndPos <= nums.size(); StartPos++, EndPos++) {
        int TempSum = 0;
        for (int i = StartPos; i < EndPos; i++) {
            TempSum += pow(nums[i], 2);
            if (TempSum > MaxValue || TempSum < 0) {
                break;
            }
        }

        if (TempSum > MaxValue || TempSum < 0) {
            return Count;
        } else {
            auto res = any_of(AllNum.begin(), AllNum.end(), [=](int i) { return i == TempSum; });
            if (res) {
                continue;
            }

            if (TempSum < 10) {
                Count++;
                AllNum.push_back(TempSum);
                continue;
            }

            int MaxDigit = ((int)log10(TempSum)) + 1;
            bool IsCorrectNum = true;
            for (int StartDigit = 1, LastDigit = MaxDigit; StartDigit < LastDigit; StartDigit++, LastDigit--) {
                int FirstNum = ((int)(TempSum / ((int)pow(10, MaxDigit - StartDigit)))) % 10;
                int SecondNum = ((int)(TempSum / ((int)(pow(10, MaxDigit - LastDigit))))) % 10;

                if (FirstNum != SecondNum) {
                    IsCorrectNum = false;
                    break;
                }
            }

            if (IsCorrectNum) {
                AllNum.push_back(TempSum);
                Count++;
                continue;
            }
        }
    }

    return Count;
}

int Palindrome::values(int v) {
    if (v < pow(1, 2) + pow(2, 2)) {
        return 0;
    }

    int MaxSquare = 1;

    while (pow(MaxSquare, 2) < v) {
        MaxSquare++;
    }

    MaxSquare--;

    std::vector<int> num;
    for (int j = 1; j <= MaxSquare; j++) {
        num.push_back(j);
    }

    int Count = 0;
    std::vector<int> AllNum;
    for (int i = 2; i <= MaxSquare; i++) {
        Count += maxSlidingWindow(num, i, v, AllNum);
    }

    return Count;
}
