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
#include <set>

using namespace std;
/*
 * @lc app=leetcode.cn id=924 lang=cpp
 *
 * [924] 尽量减少恶意软件的传播
 */

// @lc code=start
class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        vector<unordered_set<int>> group2Node;
        vector<int> node2Group(n, -1);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] == 1) {
                    if (node2Group[i] == -1 && node2Group[j] == -1) {
                        group2Node.emplace_back();
                        group2Node.back().emplace(i);
                        group2Node.back().emplace(j);
                        node2Group[i] = group2Node.size() - 1;
                        node2Group[j] = group2Node.size() - 1;
                    } else if (node2Group[i] == -1) {
                        auto groupid = node2Group[j];
                        node2Group[i] = groupid;
                        group2Node[groupid].emplace(i);
                    } else if (node2Group[j] == -1) {
                        auto groupid = node2Group[i];
                        node2Group[j] = groupid;
                        group2Node[groupid].emplace(j);
                    } else {
                        auto groupid0 = node2Group[i];
                        auto groupid1 = node2Group[j];
                        if (groupid0 == groupid1) {
                            continue;
                        }
                        for (auto tmp : group2Node[groupid1]) {
                            group2Node[groupid0].emplace(tmp);
                            node2Group[tmp] = groupid0;
                        }
                        group2Node[groupid1].clear();
                    }
                }
            }
        }
        int maxGroupSize = 0;
        int result = -1;
        set<int> initialSet(initial.begin(), initial.end());
        for (auto& group : group2Node) {
            int cnt = 0;
            int tmp = -1;
            for (auto node : group) {
                if (initialSet.count(node)) {
                    cnt++;
                    tmp = node;
                }
            }
            if (cnt == 1) {
                if (group.size() > maxGroupSize) {
                    maxGroupSize = group.size();
                    result = tmp;
                } else if (group.size() == maxGroupSize) {
                    result = std::min(tmp, result);
                }
            }
        }
        if (maxGroupSize == 0) {
           return *initialSet.begin(); 
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<std::vector<int>> graph = {{1,1,0},{1,1,0},{0,0,1}};
    std::vector<int> initial = {0, 1};
    // std::vector<std::vector<int>> graph = {{1,0,0},{0,1,0},{0,0,1}};
    // std::vector<int> initial = {0, 2};
    // std::vector<std::vector<int>> graph = {{1,1,1},{1,1,1},{1,1,1}};
    // std::vector<int> initial = {1, 2};
    // std::vector<std::vector<int>> graph = {{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1}};
    // std::vector<int> initial = {0, 1, 2};
    std::cout << sol.minMalwareSpread(graph, initial) << std::endl;
    return 0;
}
