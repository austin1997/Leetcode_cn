#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <unordered_map>
#include <utility/TreeNode.h>

using namespace std;

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
    TreeNode* replaceValueInTree(TreeNode* root) {
        std::deque<std::pair<TreeNode*, TreeNode*>> queue;
        queue.emplace_back(root, nullptr);
        while(!queue.empty()) {
            auto length = queue.size();
            std::unordered_map<TreeNode*, int64_t> map;
            std::vector<std::pair<TreeNode*, TreeNode*>> vec;
            int64_t sum = 0;
            for (int i = 0; i < length; i++) {
                auto item = queue.front();
                auto node = item.first;
                auto parent = item.second;
                vec.emplace_back(item);
                queue.pop_front();
                if (node->left != nullptr) {
                    queue.emplace_back(node->left, node);
                }
                if (node->right != nullptr) {
                    queue.emplace_back(node->right, node);
                }
                sum += node->val;
                auto iter = map.emplace(parent, 0);
                iter.first->second += node->val;
            }
            for (auto& item : vec) {
                auto node = item.first;
                auto parent = item.second;
                node->val = sum - map[parent];
            }
        }
        return root;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    TreeNode one(1, nullptr, nullptr);
    TreeNode ten(10, nullptr, nullptr);
    TreeNode seven(7, nullptr, nullptr);
    TreeNode four(4, &one, &ten);
    TreeNode nine(9, nullptr, &seven);
    TreeNode five(5, &four, &nine);

    sol.replaceValueInTree(&five);
    
    return 0;
}
