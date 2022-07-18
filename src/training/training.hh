//
// Created by Augus on 2020/6/6.
//

#ifndef AUGUSTEST_TRAINING_HH
#define AUGUSTEST_TRAINING_HH

#include "augus.h"

using augus::ListNode;
using augus::PrintTest;
using binary_tree::TreeNode;

namespace leetcode {

class LCSolution;

using LCSolution_sptr = std::shared_ptr<LCSolution>;

class LCSolution {
 public:
    static LCSolution_sptr instance();

 private:


    //前缀和
    std::vector<std::vector<int>> prefixSum(std::vector<std::vector<int>>);

};  // class LCSolution

}  // namespace leetcode

namespace codewars {

class CWSolution {
    /// 6 kyu
    /// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these
    /// multiples is 23. Finish the solution so that it returns the sum of all the multiples of 3 or 5 below the number
    /// passed in. Note: If the number is a multiple of both 3 and 5, only count it once.
    int Multiples3Or5(int number);

    /// 6 kyu Valid Braces
    bool validBraces(std::string braces);
};

/// 4 kyu Snail
class SnailSort {
 private:
    enum Pos {
        RIGHT = 0,
        DOWN,
        LEFT,
        UP,
    };

 public:
    int GetDirection(bool Direction[4]);

    bool IsArrived(int CurrentPosX, int CurrentPosY, int FinalPosX, int FinalPosY);

    std::vector<int> snail(const std::vector<std::vector<int>> &snail_map, bool isOthers);

    std::vector<int> snail(const std::vector<std::vector<int>> &snail_map);
};  // class SnailSort

/// 6 kyu Casino chips
struct Casino {
    int ColorCount(std::vector<int> v);

    int solution(std::vector<int> v);
};  // class Casino

/// 5 kyu Palindrome integer composition
class Palindrome {
 public:
    int maxSlidingWindow(const std::vector<int> &nums, int k, int MaxValue, std::vector<int> &AllNum);

    int values(int v);
};  // class Palindrome

}  // namespace codewars

#endif  // AUGUSTEST_TRAINING_HH
