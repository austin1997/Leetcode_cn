#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <Node.h>
#include <deque>

using namespace std;

/*
 * @lc app=leetcode.cn id=589 lang=cpp
 *
 * [589] N 叉树的前序遍历
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
    vector<int> preorder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        deque<Node *> stack;
        vector<int> result;
        stack.emplace_back(root);
        while (!stack.empty()) {
            auto current = stack.back();
            stack.pop_back();
            result.emplace_back(current->val);
            for (auto iter = current->children.rbegin(); iter != current->children.rend(); ++iter) {
                stack.emplace_back(*iter);
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::vector<int> stones = {5,3,1,4,2};
    std::vector<int> stones = {7,90,5,1,100,10,10,2};
    std::cout << sol.stoneGameVII(stones) << std::endl;
    return 0;
}
