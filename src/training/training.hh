//
// Created by Augus on 2020/6/6.
//

#ifndef AUGUSTEST_TRAINING_HH
#define AUGUSTEST_TRAINING_HH

#include "augus/augus.h"

using binary_tree::TreeNode;
using augus::PrintTest;

namespace leetcode {

    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };//struct ListNode

    class TrainingTreeNode {
    public:
        std::vector<int> preorderTraversal(TreeNode *root);

        std::vector<int> inorderTraversal(TreeNode *root);

        TreeNode *insertNode(TreeNode *root, int val);

        int getBalance(TreeNode *root);

        int getHeight(TreeNode *root);

        TreeNode *ll_rotate(TreeNode *y);

        TreeNode *rr_rotate(TreeNode *y);

        int buildAVL();
    };//class TrainingTreeNode

    class LCSolution;

    using LCSolution_sptr = std::shared_ptr<LCSolution>;

    class LCSolution {
    public:
        static LCSolution_sptr instance();
        /// LeetCode Sol
    public:
        /// 1
        std::vector<int> twoSum(std::vector<int> &nums, int target);

        /// 2
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);

        /// 3
        int lengthOfLongestSubstring(std::string s);

        /// 4 寻找两个正序数组的中位数      数组 二分查找 分治
        double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2);

        //7
        int reverse(int x);

        // 13 罗马数字转整数
        int romanToInt(std::string s);

        //34
        std::vector<int> searchRange(std::vector<int> &nums, int target);

        /// 45
        int jump(std::vector<int> &nums);

        //53 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
        int maxSubArray(std::vector<int> &nums);

        //58 求末尾单词的长度
        int lengthOfLastWord(std::string s);

        //111. Minimum Depth of Binary Tree
        int minDepth(TreeNode *root);

        //121、买卖股票的最佳时机  Best Time to Buy and Sell Stock IV
        int maxProfit(int k, std::vector<int> &prices);

        /// 149 Max Points on a Line
        int maxPoints(std::vector<std::vector<int>> &points);

        /// 164 Maximum Gap
        int maximumGap(std::vector<int> &nums);

        //168 给定一个正整数，返回它在 Excel 表中相对应的列名称。
        std::string convertToTitle(int columnNumber);

        //171 给定一个Excel表格中的列名称，返回其相应的列序号。
        int titleToNumber(std::string columnTitle);

        //172 阶乘后的0
        int trailingZeroes(int n);

        //191 二进制1的个数
        int hammingWeight(uint32_t n) { return std::bitset<32>(n).count(); }

        ///239. Sliding Window Maximum
        std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k);

        std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k, bool isOthers);

        //401 二进制手表
        std::vector<std::string> readBinaryWatch(int turnedOn, bool brute_force);

        std::vector<std::string> readBinaryWatch(int turnedOn, int brute_force);

        //413等差数列划分
        int numberOfArithmeticSlices(std::vector<int> &nums);

        ///421. 数组中两个数的最大异或值
        int findMaximumXOR(std::vector<int> &nums);

        /// 442
        std::vector<int> findDuplicates(std::vector<int> &nums);

        /// 448
        std::vector<int> findDisappearedNumbers(std::vector<int> &nums);

        // 653
        bool findTarget(TreeNode *root, int k);

        //682 棒球比赛
        int calPoints(std::vector<std::string> &ops);

        //1833
        int maxIceCream(std::vector<int> &costs, int coins);

        //1846
        int maximumElementAfterDecrementingAndRearranging(std::vector<int> &arr);

        //1877
        int minPairSum(std::vector<int> &nums);

        //1893 检查是否区域内所有整数都被覆盖
        bool isCovered(std::vector<std::vector<int>> &ranges, int left, int right);

        //2028 找出缺失的观测数据
        std::vector<int> missingRolls(std::vector<int> &rolls, int mean, int n);

    private:
        //计算二进制中1的个数
        int count1ofBinary(int n);

        //前缀和
        std::vector<std::vector<int>> prefixSum(std::vector<std::vector<int>>);

        //653 value
        std::set<int> ss653;
    };//class LCSolution

}//namespace leetcode

namespace codewars {


    class CWSolution {
        /// 6 kyu
        ///If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
        ///Finish the solution so that it returns the sum of all the multiples of 3 or 5 below the number passed in.
        ///Note: If the number is a multiple of both 3 and 5, only count it once.
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
    };//class SnailSort

/// 6 kyu Casino chips
    struct Casino {
        int ColorCount(std::vector<int> v);

        int solution(std::vector<int> v);
    };//class Casino

/// 5 kyu Palindrome integer composition
    class Palindrome {
    public:
        int maxSlidingWindow(const std::vector<int> &nums, int k, int MaxValue, std::vector<int> &AllNum);

        int values(int v);
    };//class Palindrome

}//namespace codewars

#endif //AUGUSTEST_TRAINING_HH
