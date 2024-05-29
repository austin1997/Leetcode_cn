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
#include <TreeNode.h>

using namespace std;

/*
 * @lc app=leetcode.cn id=894 lang=cpp
 *
 * [894] 所有可能的真二叉树
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
    static TreeNode* clone(const TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        auto result = new TreeNode();
        result->left = clone(root->left);
        result->right = clone(root->right);
        return result;
    }

    static void clean(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        clean(root->left);
        clean(root->right);
        delete root;
    }

    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> result;
        if (n <= 0 || n % 2 == 0) {
            return result;
        }
        if (n == 1) {
            result.push_back(new TreeNode());
            return result;
        }
        vector<vector<TreeNode*>> nextRoots;
        for (int i = n - 2; i >= 0; i -= 2) {
            nextRoots.push_back(allPossibleFBT(i));
        }
        
        for (int i = 0; i < nextRoots.size(); i++) {
            auto j = nextRoots.size() - 1 - i;
            for (int a = 0; a < nextRoots[i].size(); a++) {
                for (int b = 0; b < nextRoots[j].size(); b++) {
                    auto root = new TreeNode();
                    root->left = clone(nextRoots[i][a]);
                    root->right = clone(nextRoots[j][b]);
                    result.push_back(root);
                }
            }
        }
        for (auto roots : nextRoots) {
            for (auto root : roots) {
                clean(root);
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    auto tmp = sol.allPossibleFBT(7);
    std::cout << tmp.size() << std::endl;
    for (auto root : tmp) {
        Solution::clean(root);
    }
    return 0;
}
