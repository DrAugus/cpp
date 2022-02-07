//
// Created by AUGUS on 2021/3/10.
//

#ifndef AUGUSTEST_FOR_TRAINING_HH
#define AUGUSTEST_FOR_TRAINING_HH

#include <vector> // for std::vector
#include <iostream> // for std::cout
#include <stack> // for std::stack
#include <valarray> // for std::valarray std::max_element std::min_element std::sort
#include <unordered_set> // for std::unordered_set
#include <set> // for std::set
#include <list> // for std::list
#include <functional> // for std::function for std::greater_equal
#include <map> // for std::map
#include <cmath> // for std::min
#include <tuple>

#include "augus/augus.h"
#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

namespace basic_cpp {

    class ComplexDefine {
    public:
        ComplexDefine();
        ~ComplexDefine();
    };

    class OPChar {
    public:
        OPChar();
        int opWchar();
    };

    struct OPDecltype {
        inline bool isPrimaryCard(int val) {
            return val == 0x31 || val == 0x4e;
        }

        auto newPrimary(int val) -> decltype(isPrimaryCard(val)) {
            if (val == 0x22) { return isPrimaryCard(val); }
            return false;
        }
    };

    class OPSwap {
    public:
        OPSwap(int *a, int *b);
        int test();
    };

    class SomeSort {
    public:
        int libFuc();
    };
} //namespace basic_cpp

namespace sizeof_val {
    int test();
} //namespace sizeof_val

namespace op_list {
    int commonOP();

//数组 字符串 都在这里
    namespace op_array {

        class Duplicate {
        public:
            bool isContainsDuplicate(const std::vector<int> &v);

            int findDuplicateElements(int *arr, int length, std::set<int> s, std::vector<int> &output);

            int Test();
        };//class Duplicate

        class VectorCtrl {
        public:
            // 寻找元素在Vector的位置
            int findPosVector(std::vector<int> input, int number);

            int findVectorSub();

            //容器vector中元素的去重
            std::vector<int> unique_element_in_vector(std::vector<int> v);

            //两个vector求交集
            std::vector<int> vectors_intersection(std::vector<int> v1, std::vector<int> v2);

            //两个vector求并集
            std::vector<int> vectors_set_union(std::vector<int> v1, std::vector<int> v2);
        };//class VectorCtrl

        class ArrayLength {
        public:
            ArrayLength();
        };//class ArrayLength

        class LC {
        public:
            //寻找数组的中心索引
            int pivotIndex(std::vector<int> &nums);
            //搜索插入位置
            int searchInsert(std::vector<int> &nums, int target);
            //旋转矩阵
            void rotate(std::vector<std::vector<int>> &matrix);
            //零矩阵
            void setZeroes(std::vector<std::vector<int>> &matrix);
            //最长公共前缀
            std::string longestCommonPrefix(std::vector<std::string> &strs);

            void test();

        };//class LC

        std::vector<int> mergeTest(std::vector<int> &nums1, unsigned m, std::vector<int> &nums2, unsigned n);
        int findMaxInArray();
        int commonVectorOP();
        int switchArr2Vec();
//[1,2,2,3,1,4,2]
        int findShortestSubArray(std::vector<int> &nums);

    } //namespace op_array
} //namespace op_list

namespace binary_tree {
    struct TreeNode {
        int value;
        int height;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : value(0), height(0), left(nullptr), right(nullptr) {}
        explicit TreeNode(int val) : value(val), height(1), left(nullptr), right(nullptr) {}
        TreeNode(int val, int h, TreeNode *left, TreeNode *right) : value(val), height(h), left(left), right(right) {}
    };//struct TreeNode

    struct BinaryTree {
        void preOrderRecur(TreeNode *head);
        void inOrderRecur(TreeNode *head);
        void posOrderRecur(TreeNode *head);
        void preOrderUnRecur(TreeNode *head);
        void inOrderUnRecur(TreeNode *head);
        void posOrderUnRecur(TreeNode *head);
        int test();

    };//struct BinaryTree

} //namespace binary_tree

namespace primary_algorithms {


    void reverse_array(std::vector<int> &nums, int begin, int end);


    struct pa_array {
        //删除排序数组中的重复项
        int removeDuplicates(std::vector<int> &nums, double point);// double point means 双指针
        int removeDuplicates(std::vector<int> &nums);
        int removeDuplicates(std::vector<int> &nums, bool use_stl);
        //买卖股票的最佳时机 II
        int maxProfit(std::vector<int> &prices);
        //旋转数组
        void rotate(std::vector<int> &nums, int k);
        void rotate(std::vector<int> &nums, int k, double other_array);//临时数组
        void rotate(std::vector<int> &nums, int k, bool use_stl);
        //存在重复元素
        bool containsDuplicate(std::vector<int> &nums);
        bool containsDuplicate(std::vector<int> &nums, bool use_stl);
        //只出现一次的数字
        int singleNumber(std::vector<int> &nums);
        int singleNumber(std::vector<int> &nums, bool use_set);
        //两个数组的交集 II
        std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2);
        std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2, bool use_stl);
    };

}//namespace primary_algorithms


//https://changkun.de/modern-cpp/en-us/00-preface/
namespace modern_cpp {

    void usabilityEnhancements();

    //结构化绑定
    std::tuple<int, double, std::string> fTuple();

    //decltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的。它的用法和 typeof 很相似
    void testIsSame();

}


#endif //AUGUSTEST_FOR_TRAINING_HH
