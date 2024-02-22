#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <Node.h>
#include <deque>

using namespace std;

/*
 * @lc app=leetcode.cn id=590 lang=cpp
 *
 * [590] N 叉树的后序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:

    void helper(Node *root, vector<int> &result) {
        if (root == nullptr) {
            return;
        }
        for (auto node : root->children) {
            helper(node, result);
        }
        result.emplace_back(root->val);
    }

    vector<int> postorder(Node* root) {
        vector<int> result;
        helper(root, result);
        return result;
    }

    vector<int> postorder2(Node* root) {
        
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    return 0;
}
