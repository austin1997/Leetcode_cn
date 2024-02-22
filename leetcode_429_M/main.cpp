#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <Node.h>
#include <deque>

using namespace std;

/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N 叉树的层序遍历
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
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        vector<vector<int>> result;
        deque<Node *> queue;
        queue.emplace_back(root);
        while (!queue.empty()) {
            result.emplace_back(vector<int>());
            auto &tmp = result.back();
            auto size = queue.size();
            for (int i = 0; i < size; i++) {
                auto curr = queue.front();
                queue.pop_front();
                tmp.emplace_back(curr->val);
                queue.insert(queue.end(), curr->children.begin(), curr->children.end());
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    return 0;
}
