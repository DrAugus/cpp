//
// utils.h
// Created by AUGUS on 2022/7/18.
//

#ifndef AUGUS_CPP_UTILS_H
#define AUGUS_CPP_UTILS_H

#include <memory>

namespace leetcode {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        explicit ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };  // struct ListNode

    struct TreeNode {
        int value;
        int height;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : value(0), height(0), left(nullptr), right(nullptr) {}
        explicit TreeNode(int val) : value(val), height(1), left(nullptr), right(nullptr) {}
        TreeNode(int val, int h, TreeNode *left, TreeNode *right)
                : value(val), height(h), left(left), right(right) {}
    };  // struct TreeNode

    class Utils {
    public:
        int hammingWeight(int n) {
            int res = 0;
            while (n) {
                n &= (n - 1);
                res++;
            }
            return res;
        }
    public:
        Utils() = default;
        ~Utils()=default;
    };
    using utils_ptr = std::shared_ptr<Utils>;
}

#endif //AUGUS_CPP_UTILS_H
