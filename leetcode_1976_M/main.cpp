#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

/*
 * @lc app=leetcode.cn id=1976 lang=cpp
 *
 * [1976] 到达目的地的方案数
 */

// @lc code=start
class Solution {
public:

    int64_t add(int64_t a, int64_t b) {
        const int64_t tmp = 1e9 + 7;
        return (a + b) % tmp;
    }

    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<vector<int>>> roadMap(n);
        for (auto &road : roads) {
            vector<int> tmp = {road[1], road[2]};
            roadMap[road[0]].emplace_back(tmp);
            tmp = {road[0], road[2]};
            roadMap[road[1]].emplace_back(tmp);
        }
        vector<int64_t> tmp = {numeric_limits<int64_t>::max(), 0};
        vector<vector<int64_t>> dp(n, tmp);  // cost, cnt
        dp[0] = {0, 1};
        vector<int> distanceOrder(n);
        std::iota(distanceOrder.begin(), distanceOrder.end(), 0);
        auto cmpDistance = [&](auto a, auto b) -> bool {
            return dp[a][0] < dp[b][0];
        };
        for (int i = 0; i < n; i++) {
            std::sort(distanceOrder.begin(), distanceOrder.end(), cmpDistance);
            auto curr = distanceOrder[i];
            auto &currEntry = dp[curr];
            // for (auto &road : roadMap[curr]) {
            //     if (dp[road[0]][0] >= numeric_limits<int64_t>::max()) {
            //         continue;
            //     }
            //     auto cost = road[1] + dp[road[0]][0];
            //     if (cost < currEntry[0]) {
            //         currEntry = {cost, dp[road[0]][1]};
            //     } else if (cost == currEntry[0]) {
            //         currEntry[1]++;
            //     }
            // }
            for (auto &road : roadMap[curr]) {
                auto cost = road[1] + currEntry[0];
                if (cost < dp[road[0]][0]) {
                    dp[road[0]] = {cost, currEntry[1]};
                } else if (cost == dp[road[0]][0]) {
                    dp[road[0]][1] = add(dp[road[0]][1], currEntry[1]);
                }
            }
        }
        return dp.back().back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    // std::vector<vector<int>> in1 = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
    // std::cout << sol.countPaths(7, in1) << std::endl;

    std::vector<vector<int>> in1 = {{1,0,10}};
    std::cout << sol.countPaths(2, in1) << std::endl;

    return 0;
}
