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
 * @lc app=leetcode.cn id=2867 lang=cpp
 *
 * [2867] 统计树中的合法路径数目
 */

// @lc code=start
class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    void buildTree(const vector<vector<int>>& edges) {
        unordered_map<int, int> redirectMap;
        auto resolveRedirects = [&redirectMap](int id) {
            auto iter = redirectMap.find(id);
            if (iter == redirectMap.end()) {
                return 0;
            }
            vector<unordered_map<int, int>::iterator> tmp;
            while (iter->second != iter->first) {
                iter = redirectMap.find(iter->second);
                tmp.push_back(iter);
            }
            for (auto item : tmp) {
                item->second = iter->first;
            }
            return iter->first;
        };
        for (const auto &edge : edges) {
            auto node0 = resolveRedirects(edge[0]);
            auto node1 = resolveRedirects(edge[1]);
            if (!primes.count(edge[0]) && !primes.count(edge[1])) {
                if (node0 != 0 && node1 != 0) {
                    nodeWeights[node0] += nodeWeights[node1];
                    nodeWeights.erase(node1);
                    auto &tmp = nodeEdges[node1];
                    nodeEdges[node0].insert(tmp.begin(), tmp.end());
                    nodeEdges.erase(node1);
                    redirectMap[node1] = node0;
                } else if (node0 != 0) {
                    node1 = edge[1];
                    nodeWeights[node0]++;
                    redirectMap[node1] = node0;
                } else if (node1 != 0) {
                    node0 = edge[0];
                    nodeWeights[node1]++;
                    redirectMap[node0] = node1;
                } else {
                    node0 = edge[0];
                    node1 = edge[1];
                    nodeWeights[node0] = 2;
                    redirectMap[node0] = node0;
                    redirectMap[node1] = node0;
                }
            } else {
                if (node0 == 0) {
                    node0 = edge[0];
                    nodeWeights[node0] = 1;
                    redirectMap[node0] = node0;
                }
                if (node1 == 0) {
                    node1 = edge[1];
                    nodeWeights[node1] = 1;
                    redirectMap[node1] = node1;
                }
                nodeEdges[node0].emplace(node1);
                nodeEdges[node1].emplace(node0);
            }
        }
    }

    long long countPaths(int n, vector<vector<int>>& edges) {
        for (int i = 0; i <= n; i++) {
            if (isPrime(i)) {
                primes.emplace(i);
            }
        }
        
        buildTree(edges);
        
        long long result = 0;
        for (auto prime : primes) {
            // result += countPaths(prime);
            auto iterWeight = nodeWeights.find(prime);
            if (iterWeight == nodeWeights.end()) {
                continue;
            }
            long long curr = 0;
            for (auto &edge : nodeEdges[prime]) {
                if (!primes.count(edge)) {
                    auto tmp = nodeWeights[edge];
                    result += curr * tmp;
                    curr += tmp;
                }
            }
            result += curr;
        }
        return result;
    }
    unordered_map<int, int> nodeWeights;
    unordered_map<int, unordered_set<int>> nodeEdges;
    unordered_set<int> primes;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<std::vector<int>> q = {{1,2},{1,3},{2,4},{2,5}};
    std::cout << sol.countPaths(5, q) << std::endl;

    // std::vector<std::vector<int>> q = {{1,2},{1,3},{2,4},{3,5},{3,6}};
    // std::cout << sol.countPaths(6, q) << std::endl;

    // std::vector<std::vector<int>> q = {{2,3},{2,4},{3,1},{5,1}};
    // std::cout << sol.countPaths(5, q) << std::endl;
    return 0;
}
