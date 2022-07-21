//
// 111.cpp
// Created by AUGUS on 2022/7/18.
// Minimum Depth of Binary Tree
//

#include <utils.h>
#include <cmath>

namespace leetcode {
    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int lDepth = minDepth(root->left);
        int rDepth = minDepth(root->right);

        if (lDepth == 0) {
            return rDepth + 1;
        } else if (rDepth == 0) {
            return lDepth + 1;
        } else {
            return std::min(lDepth, rDepth) + 1;
        }
    }
}

int main() { return 1; }