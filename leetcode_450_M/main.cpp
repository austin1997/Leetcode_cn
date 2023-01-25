#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <TreeNode.h>

using namespace std;

class Solution {
public:

    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val > key && root->left != nullptr) {
            root->left = deleteNode(root->left, key);
        }
        if (root->val < key && root->right != nullptr) {
            root->right = deleteNode(root->right, key);
        }
        if (root->val != key) {
            return root;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr;
        }
        if (root->left != nullptr && root->right == nullptr) {
            return root->left;
        }
        if (root->left == nullptr && root->right != nullptr) {
            return root->right;
        }
        auto prev = root->left;
        while (prev->right != nullptr) {
            prev = prev->right;
        }
        root->val = prev->val;
        root->left = deleteNode(root->left, root->val);
        return root;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
    vector<TreeNode *> nodes(8, nullptr);
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i] = new TreeNode(i);
    }
    nodes[5]->left = nodes[3];
    nodes[5]->right = nodes[6];
    nodes[3]->left = nodes[2];
    nodes[3]->right = nodes[4];
    nodes[6]->right = nodes[7];
    auto tmp = sol.deleteNode(nodes[5], 3);
    cout << tmp << endl;

    for (auto node : nodes) {
        delete node;
    }
    return 0;
}
