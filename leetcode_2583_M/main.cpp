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
 * @lc app=leetcode.cn id=2583 lang=cpp
 *
 * [2583] 二叉树中的第 K 大层和
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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        priority_queue<long long> sumQueue;
        queue<TreeNode *> nodeQueue;
        nodeQueue.emplace(root);
        while (!nodeQueue.empty()) {
            auto size = nodeQueue.size();
            long long sum = 0;
            for (int i = 0; i < size; i++) {
                auto node = nodeQueue.front();
                nodeQueue.pop();
                sum += node->val;
                if (node->left != nullptr) {
                    nodeQueue.emplace(node->left);
                }
                if (node->right != nullptr) {
                    nodeQueue.emplace(node->right);
                }
            }
            sumQueue.emplace(sum);
        }
        if (sumQueue.size() < k) {
            return -1;
        }
        for (int i = 0; i < k - 1; i++) {
            sumQueue.pop();
        }
        return sumQueue.top();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::cout << sol.kthLargestLevelSum(new) << std::endl;
    return 0;
}
