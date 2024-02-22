#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <TreeNode.h>
#include <deque>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=106 lang=cpp
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
    TreeNode* buildTree(vector<int>& inorder, int inorderStart, int inorderEnd, vector<int>& postorder, int postorderStart, int postorderEnd) {
        if (inorderStart > inorderEnd || postorderStart > postorderEnd) {
            return nullptr;
        }
        auto val = postorder[postorderEnd];
        auto index = inorderIndex[val];
        auto leftSize = index - inorderStart;
        auto left = buildTree(inorder, inorderStart, index - 1, postorder, postorderStart, postorderStart + leftSize - 1);
        auto rightSize = inorderEnd + 1 - index;
        auto right = buildTree(inorder, index + 1, inorderEnd, postorder, postorderStart + leftSize, postorderEnd - 1);
        auto node = new TreeNode(val, left, right);
        return node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderIndex[inorder[i]] = i;
        }
        return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    unordered_map<int, int> inorderIndex;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    std::cout << sol.buildTree(inorder, postorder)->val << std::endl;
    return 0;
}
