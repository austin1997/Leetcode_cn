#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <TreeNode.h>
#include <deque>
#include <queue>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=938 lang=cpp
 *
 * [938] 二叉搜索树的范围和
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
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return 0;
        }
        int result = 0;
        if (root->val >= low && root->val <= high) {
            result = root->val;
        }
        return result + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::cout << sol.kthLargestLevelSum(new) << std::endl;
    return 0;
}
