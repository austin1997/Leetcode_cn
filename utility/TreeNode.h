//
// Created by austi on 2022/6/1.
//

#ifndef LEETCODE_CN_TREENODE_H
#define LEETCODE_CN_TREENODE_H


#include <deque>

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

    static TreeNode *parseString(std::string &str) {
        return nullptr;
    }

    ~TreeNode() {
        delete left;
        delete right;
    }
};


#endif //LEETCODE_CN_TREENODE_H
