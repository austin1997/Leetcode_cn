#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=2581 lang=cpp
 *
 * [2581] 统计可能的树根数目
 */

// @lc code=start
class Solution {
public:

    int initTreeRoot(int root) {
        int result = 0;
        unordered_set<int> visited;
        queue<int> nodeQueue;
        nodeQueue.emplace(root);
        while (!nodeQueue.empty()) {
            auto curr = nodeQueue.front();
            nodeQueue.pop();
            visited.emplace(curr);
            for (auto edge : treeEdges[curr]) {
                if (visited.count(edge)) {
                    continue;
                }
                if (unmatchedGuesses[curr].erase(edge)) {
                    matchedGuesses[curr].emplace(edge);
                    result++;
                }
                nodeQueue.emplace(edge);
            }
        }
        return result;
    }

    int rootCount(int root, int matchedCnt, int k) {
        int result = 0;
        unordered_set<int> visited;
        visited.emplace(root);
        deque<std::pair<int, int>> nodeQueue;
        for (auto& edge : treeEdges[root]) {
            nodeQueue.emplace_back(edge, root);
        }
        if (matchedCnt >= k) {
            result++;
        }
        while (!nodeQueue.empty()) {
            auto node = nodeQueue.back();
            auto curr = node.first;
            auto parent = node.second;
            if (visited.count(curr)) {
                auto matchedExist = matchedGuesses[curr].erase(parent);
                auto unmatchedExist = unmatchedGuesses[parent].erase(curr);
                if (matchedExist) {
                    unmatchedGuesses[curr].emplace(parent);
                    matchedCnt--;
                }
                if (unmatchedExist) {
                    matchedGuesses[parent].erase(curr);
                    matchedCnt++;
                }
                nodeQueue.pop_back();
                continue;
            } else {
                
                auto matchedExist = matchedGuesses[parent].erase(curr);
                auto unmatchedExist = unmatchedGuesses[curr].erase(parent);
                if (matchedExist) {
                    unmatchedGuesses[parent].emplace(curr);
                    matchedCnt--;
                }
                if (unmatchedExist) {
                    matchedGuesses[curr].emplace(parent);
                    matchedCnt++;
                }
                
                if (matchedCnt >= k) {
                    result++;
                }
            }
            
            for (auto &edge : treeEdges[curr]) {
                if (!visited.count(edge)) {
                    nodeQueue.emplace_back(edge, curr);
                }
            }
            visited.emplace(curr);
        }
        
        return result;
    }

    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        treeEdges.resize(n);
        matchedGuesses.resize(n);
        unmatchedGuesses.resize(n);
        for (auto &edge : edges) {
            treeEdges[edge[0]].push_back(edge[1]);
            treeEdges[edge[1]].push_back(edge[0]);
        }
        for (auto &edge : guesses) {
            unmatchedGuesses[edge[0]].emplace(edge[1]);
        }
        
        auto matchedCnt = initTreeRoot(0);
        return rootCount(0, matchedCnt, k);
    }

    vector<vector<int>> treeEdges;
    vector<unordered_set<int>> matchedGuesses;
    vector<unordered_set<int>> unmatchedGuesses;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    // std::vector<std::vector<int>> in1 = {{0,1},{1,2},{1,3},{4,2}};
    // std::vector<std::vector<int>> in2 = {{1,3},{0,1},{1,0},{2,4}};
    // std::cout << sol.rootCount(in1, in2, 3) << std::endl;

    // std::vector<std::vector<int>> in1 = {{0,1},{1,2},{2,3},{3,4}};
    // std::vector<std::vector<int>> in2 = {{1,0},{3,4},{2,1},{3,2}};
    // std::cout << sol.rootCount(in1, in2, 1) << std::endl;

    std::vector<std::vector<int>> in1, in2;
    for (int i = 0; i < 100000 - 1; i++) {
        std::vector<int> tmp = {i, i + 1};
        in1.emplace_back(tmp);
        if (i % 2 != 0) {
            tmp = {i, i - 1};
            in2.emplace_back(tmp);
            tmp = {i, i + 1};
            in2.emplace_back(tmp);
        }
    }
    in2.pop_back();
    std::cout << sol.rootCount(in1, in2, 50000) << std::endl;
    return 0;
}
