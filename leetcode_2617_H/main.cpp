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

using namespace std;

/*
 * @lc app=leetcode.cn id=2617 lang=cpp
 *
 * [2617] 网格图中最少访问的格子数
 */

// @lc code=start
class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid.front().size();
        vector<vector<int>> dp(m, vector<int>(n, numeric_limits<int>::max()));
        vector<vector<pair<int, int>>> span(m, vector<pair<int, int>>(n, pair<int, int>(0, 0)));
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        dp[0][0] = 1;
        while (!q.empty()) {
            auto tmp = q.front();
            q.pop();
            auto i = tmp.first;
            auto j = tmp.second;
            auto curr = dp[i][j];
            auto spanX = span[i][j].first;
            auto spanY = span[i][j].second;
            for (int k = j + spanY + 1; k < n && k <= grid[i][j] + j; k++) {
                if (curr + 1 < dp[i][k]) {
                    dp[i][k] = curr + 1;
                    q.emplace(i, k);
                }
                if (curr + 1 <= dp[i][k]) {
                    span[i][k].second = std::max(grid[i][j] - (k - j), span[i][k].second);
                }
            }
            for (int k = i + spanX + 1; k < m && k <= grid[i][j] + i; k++) {
                if (curr + 1 < dp[k][j]) {
                    dp[k][j] = curr + 1;
                    q.emplace(k, j);
                }
                if (curr + 1 <= dp[k][j]) {
                    span[k][j].first = std::max(grid[i][j] - (k - i), span[k][j].first);
                }
            }
        }
        if (dp.back().back() == numeric_limits<int>::max()) {
            return -1;
        }
        return dp.back().back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<vector<int>> grid = {{3,4,2,1},{4,2,3,1},{2,1,0,0},{2,4,0,0}};
    std::cout << sol.minimumVisitedCells(grid) << std::endl;

    // vector<vector<int>> grid = {{3,4,2,1},{4,2,1,1},{2,1,1,0},{3,4,1,0}};
    // std::cout << sol.minimumVisitedCells(grid) << std::endl;
    return 0;
}
