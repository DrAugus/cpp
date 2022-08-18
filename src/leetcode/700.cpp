//
// Created by AUGUS on 2022/7/30.
// 二叉搜索树中的搜索
//

#include "utils.h"

namespace leetcode {
    TreeNode *searchBST(TreeNode *root, int val) {
        if (root == nullptr || root->value == val) return root;
        if (root->value > val) return searchBST(root->left, val);
        else return searchBST(root->right, val);
    }
}

int main() {
    return 1;
}