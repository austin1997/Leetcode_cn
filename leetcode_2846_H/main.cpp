#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
 * @lc app=leetcode.cn id=2846 lang=cpp
 *
 * [2846] 边权重均等查询
 */

// @lc code=start
class Solution
{
public:
    class Node
    {
    public:
    Node(int index = -1) : index(index) {}
    std::unordered_set<int> buildGrandsons(vector<Node> &tree) {
        unordered_set<int> result;
        for (auto &child : children) {
            auto &grandson = child.second.second;
            grandson = tree[child.first].buildGrandsons(tree);
            grandson.emplace(child.first);
            result.insert(grandson.begin(), grandson.end());
        }
        return result;
    }

    void getCosts(const vector<Node> &tree, int start, int end, std::vector<int> &costs) const {
        if (start == index) {
            start = -1;
        }
        if (end == index) {
            end = -1;
        }
        {
            auto tmp = children.find(start);
            if (tmp != children.end()) {
                costs.emplace_back(tmp->second.first);
                start = -1;
            }
            tmp = children.find(end);
            if (tmp != children.end()) {
                costs.emplace_back(tmp->second.first);
                end = -1;
            }
        }
        if (start < 0 && end < 0) {
            return;
        }

        for (auto &child : children) {
            if (child.second.second.count(start)) {
                costs.emplace_back(child.second.first);
                tree[child.first].getCosts(tree, start, end, costs);
            } else if (child.second.second.count(start)) {
                costs.emplace_back(child.second.first);
                tree[child.first].getCosts(tree, start, end, costs);
            }
        }
    }
    int index;
    unordered_map<int, std::pair<int, unordered_set<int>>> children;
    };
    
    void buildTree(int n, const vector<vector<int>> &edges) {
        tree.clear();
        tree.resize(n);
        tree[0].index = 0;
        unordered_set<int> used;
        while (used.size() < edges.size()) {
            for (int index = 0; index < edges.size(); index++) {
                if (used.count(index)) {
                    continue;
                }
                auto &edge = edges[index];
                if (tree[edge[0]].index >= 0) {
                    tree[edge[1]].index = edge[1];
                    auto iter = tree[edge[0]].children.emplace(edge[1], std::pair<int, unordered_set<int>>());
                    iter.first->second.first = edge[2];
                    used.emplace(index);
                } else if (tree[edge[1]].index >= 0) {
                    tree[edge[0]].index = edge[0];
                    auto iter = tree[edge[1]].children.emplace(edge[0], std::pair<int, unordered_set<int>>());
                    iter.first->second.first = edge[2];
                    used.emplace(index);
                }
            }
        }
        tree[0].buildGrandsons(tree);
    }

    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries)
    {
        buildTree(n, edges);
        vector<int> result;
        for (const auto &query : queries) {
            std::vector<int> costs;
            tree[0].getCosts(tree, query[0], query[1], costs);
            sort(costs.begin(), costs.end());
            int num = 1;
            int maxNum = 1;
            for (int i = 1; i < costs.size(); i++) {
                if (costs[i] == costs[i - 1]) {
                    num++;
                } else {
                    maxNum = max(num, maxNum);
                    num = 1;
                }
            }
            result.emplace_back(costs.size() - maxNum);
        }
        return result;
    }

    std::vector<Node> tree;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<vector<int>> edges = {{0,1,1},{1,2,1},{2,3,1},{3,4,2},{4,5,2},{5,6,2}};
    vector<vector<int>> queries = {{0,3},{3,6},{2,6},{0,6}};
    auto tmp = sol.minOperationsQueries(7, edges, queries);
    std::cout << tmp.size() << std::endl;
    return 0;
}
