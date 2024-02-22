#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <TreeNode.h>
#include <deque>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=889 lang=cpp
 *
 * [889] 根据前序和后序遍历构造二叉树
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
    TreeNode* constructFromPrePost(vector<int>& preorder, int preorderStart, int preorderEnd, vector<int>& postorder, int postorderStart, int postorderEnd) {
        if (preorderStart > preorderEnd || postorderStart > postorderEnd) {
            return nullptr;
        }
        if (preorderStart == preorderEnd) {
            return new TreeNode(preorder[preorderStart]);
        }
        auto leftRootVal = preorder[preorderStart + 1];
        auto leftRootIndex = postorderIndices[leftRootVal];
        auto leftSize = leftRootIndex - postorderStart + 1;
        auto left = constructFromPrePost(preorder, preorderStart + 1, preorderStart + leftSize, postorder, postorderStart, leftRootIndex);
        auto right = constructFromPrePost(preorder, preorderStart + leftSize + 1, preorderEnd, postorder, leftRootIndex + 1, postorderEnd - 1);   
        return new TreeNode(preorder[preorderStart], left, right);     
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        for (int i = 0; i < postorder.size(); i++) {
            postorderIndices[postorder[i]] = i;
        }
        return constructFromPrePost(preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    unordered_map<int, int> postorderIndices;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> inorder = {1,2,4,5,3,6,7};
    vector<int> postorder = {4,5,2,6,7,3,1};
    std::cout << sol.constructFromPrePost(inorder, postorder)->val << std::endl;
    return 0;
}
