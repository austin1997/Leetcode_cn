#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <TreeNode.h>
#include <deque>

using namespace std;

/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
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

    TreeNode* buildTree(vector<int>& preorder, int preorderStart, int& treeSize, vector<int>& inorder, int inorderStart, int inorderEnd) {
        if (preorderStart >= preorder.size() || inorderStart > inorderEnd) {
            return nullptr;
        }
        auto node = new TreeNode(preorder[preorderStart]);
        
        int inorderIndex = -1;
        for (auto i = inorderStart; i <= inorderEnd; i++) {
            if (inorder[i] == node->val) {
                inorderIndex = i;
            }
        }
        int leftSize = 0;
        auto left = buildTree(preorder, preorderStart + 1, leftSize, inorder, inorderStart, inorderIndex - 1);
        int rightSize = 0;
        auto right = buildTree(preorder, preorderStart + 1 + leftSize, rightSize, inorder, inorderIndex + 1, inorderEnd);
        treeSize = leftSize + rightSize + 1;
        node->left = left;
        node->right = right;
        return node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int treeSize = 0;
        return buildTree(preorder, 0, treeSize, inorder, 0, inorder.size() - 1);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    return 0;
}
