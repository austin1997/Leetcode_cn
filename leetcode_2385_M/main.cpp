#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <TreeNode.h>

using namespace std;
/*
 * @lc app=leetcode.cn id=2385 lang=cpp
 *
 * [2385] 感染二叉树需要的总时间
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int getHeight(TreeNode* root) {
        if (root == nullptr) {
            return -1;
        }
        auto left = getHeight(root->left);
        auto right = getHeight(root->right);
        return std::max(left, right) + 1;
    }

    int helper(TreeNode* root, int start, int& result) {
        if (root == nullptr) {
            return -1;
        }
        if (root->val == start) {
            result = getHeight(root);
            return 1;
        }
        int leftResult, rightResult;
        int leftDepth = helper(root->left, start, leftResult);
        int rightDepth = helper(root->right, start, rightResult);
        if (leftDepth != -1) {
            result = std::max(leftDepth + getHeight(root->right) + 1, leftResult);
            return leftDepth + 1;
        } else if (rightDepth != -1) {
            result = std::max(rightDepth + getHeight(root->left) + 1, rightResult);
            return rightDepth + 1;
        }
        return -1;
    }

    int amountOfTime(TreeNode* root, int start) {
        int tmp = -1;
        helper(root, start, tmp);
        return tmp;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    TreeNode* root = nullptr;
    for (int i = 5; i >= 1; i--) {
        root = new TreeNode(i, root, nullptr);
    }
    sol.amountOfTime(root, 2);
    return 0;
}
