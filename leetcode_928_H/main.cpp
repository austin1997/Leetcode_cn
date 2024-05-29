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
 * @lc app=leetcode.cn id=928 lang=cpp
 *
 * [928] 尽量减少恶意软件的传播 II
 */

// @lc code=start
class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        vector<int> nodes(n);
        std::iota(nodes.begin(), nodes.end(), 0);
        set<int> initialSet(initial.begin(), initial.end());
        int maxUninfected = 0;
        int result = *initialSet.begin();
        for (int i = 0; i < initial.size(); i++) {
            unordered_set<int> unvisited(nodes.begin(), nodes.end());
            unvisited.erase(initial[i]);
            int uninfected = 0;
            while(!unvisited.empty()) {
                auto before = unvisited.size();
                auto root = *unvisited.begin();
                queue<int> queue;
                queue.push(root);
                bool infected = false;
                int cnt = 0;
                while (!queue.empty()) {
                    cnt++;
                    auto curr = queue.front();
                    queue.pop();
                    unvisited.erase(curr);
                    if (initialSet.count(curr)) {
                        infected = true;
                    }
                    for (int j = 0; j < n; j++) {
                        if (graph[curr][j] == 1 && unvisited.count(j)) {
                            queue.push(j);
                        }
                    }
                }
                if (!infected) {
                    uninfected += cnt;
                }
            }
            if (uninfected > maxUninfected) {
                maxUninfected = uninfected;
                result = i;
            } else if (uninfected == maxUninfected) {
                result = std::min(i, result);
            }
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
    // std::vector<std::vector<int>> graph = {{1,1,0},{1,1,1},{0,1,1}};
    // std::vector<int> initial = {0, 1};
    // std::vector<std::vector<int>> graph = {{1,1,0,0},{1,1,1,0},{0,1,1,1},{0,0,1,1}};
    // std::vector<int> initial = {0, 1};
    std::cout << sol.minMalwareSpread(graph, initial) << std::endl;
    return 0;
}
