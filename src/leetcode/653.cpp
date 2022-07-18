//
// 653.cpp
// Created by AUGUS on 2022/7/18.
//

#include <utils.h>
#include <set>

namespace leetcode {

    std::set<int> ss653;

    bool findTarget(TreeNode *root, int k) {
        if (!root)
            return false;
        if (ss653.count(k - root->value)) {
            return true;
        }
        ss653.insert(root->value);
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
}