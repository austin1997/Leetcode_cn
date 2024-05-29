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
#include <TreeNode.h>

using namespace std;
/*
 * @lc app=leetcode.cn id=741 lang=cpp
 *
 * [741] 摘樱桃
 */

// @lc code=start
class Solution {
public:
    int helper(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end, pair<int, int> moveDir) {
        if (grid[start.first][start.second] == -1 || 
            grid[end.first][end.second] == -1) {
            return -1;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, 0)));
        for (int x = start.first; x != end.first + moveDir.first; x += moveDir.first) {
            for (int y = start.second; y != end.second + moveDir.second; y += moveDir.second) {
                if (grid[x][y] == -1) {
                    dp[x][y][0] = -1;
                    continue;
                }
                int left = 0;
                int right = 0;
                auto nextX = x - moveDir.first;
                auto nextY = y - moveDir.second;
                if (0 <= nextX && nextX < m) {
                    left = dp[nextX][y][0];
                } else {
                    left = -2;
                }
                if (0 <= nextY && nextY < n) {
                    right = dp[x][nextY][0];
                } else {
                    right = -2;
                }
                if (left == -1 && right == -1) {
                    dp[x][y][0] = -1;
                    continue;
                }
                dp[x][y][0] = grid[x][y] == 1 ? 1 : 0;
                if (left == -2 && right == -2) {
                    continue;
                }
                if (left > right) {
                    dp[x][y][0] += left;
                    dp[x][y][1] = nextX;
                    dp[x][y][2] = y;
                } else {
                    dp[x][y][0] += right;
                    dp[x][y][1] = x;
                    dp[x][y][2] = nextY;
                }
            }
        }
        auto result = dp[end.first][end.second][0];
        if (result == -1) {
            return -1;
        }
        int currX = end.first;
        int currY = end.second;
        while (currX != start.first || currY != start.second) {
            if (grid[currX][currY] == -1) {
                break;
            }
            grid[currX][currY] = 0;
            auto nextX = dp[currX][currY][1];
            auto nextY = dp[currX][currY][2];
            currX = nextX;
            currY = nextY;
        }
        if (grid[start.first][start.second] == 1) {
            grid[start.first][start.second] = 0;
        }
        return result;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        if (grid[0][0] == -1) {
            return 0;
        }
        int m = grid.size();
        int n = grid.front().size();
        vector<vector<vector<int>>> dp(m + n - 1, vector<vector<int>>(m, vector<int>(n, 0)));
        dp[0][0][0] = grid[0][0] == 1 ? 1 : 0;
        for (int k = 1; k <= m + n - 2; k++) {
            for (int x1 = std::max(k - n + 1, 0); x1 <= k && x1 < m; x1++) {
                auto y1 = k - x1;
                for (int x2 = std::max(k - n + 1, 0); x2 <= k && x2 < m; x2++) {
                    auto y2 = k - x2;
                    if (grid[x1][y1] == -1 || grid[x2][y2] == -1) {
                        dp[k][x1][x2] = numeric_limits<int>::min();
                        continue;
                    }
                    int curr = 0;
                    if (grid[x1][y1] == 1) {
                        curr++;
                    }
                    if (grid[x2][y2] == 1 && x1 != x2) {
                        curr++;
                    }
                    int best = numeric_limits<int>::min();
                    if (k - 1 >= x1 && k - 1 >= x2) {
                        best = dp[k - 1][x1][x2];
                    }
                    if (x1 > 0 && x2 <= k - 1) {
                        best = std::max(dp[k - 1][x1 - 1][x2], best);
                    }
                    if (x2 > 0 && x1 <= k - 1) {
                        best = std::max(dp[k - 1][x1][x2 - 1], best);
                    }
                    if (x1 > 0 && x2 > 0) {
                        best = std::max(dp[k - 1][x1 - 1][x2 - 1], best);
                    }
                    dp[k][x1][x2] = curr + best;
                }
            }
        }
        return std::max(dp[m + n - 2][m - 1][n - 1], 0);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // vector<vector<int>> grid = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
    // vector<vector<int>> grid = {{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};
    // vector<vector<int>> grid = {{1,1,1,1,0,0,0},
    //                             {0,0,0,1,0,0,0},
    //                             {0,0,0,1,0,0,1},
    //                             {1,0,0,1,0,0,0},
    //                             {0,0,0,1,0,0,0},
    //                             {0,0,0,1,0,0,0},
    //                             {0,0,0,1,1,1,1}};
    vector<vector<int>> grid = {{ 1,-1, 1,-1, 1,1, 1, 1,1,-1},
                                {-1, 1, 1,-1,-1,1, 1, 1,1, 1},
                                { 1, 1, 1,-1, 1,1, 1, 1,1, 1},
                                { 1, 1, 1, 1, 1,1, 1, 1,1, 1},
                                {-1, 1, 1, 1, 1,1, 1, 1,1, 1},
                                { 1,-1, 1, 1, 1,1,-1, 1,1, 1},
                                { 1, 1, 1,-1, 1,1,-1, 1,1, 1},
                                { 1,-1, 1,-1,-1,1, 1, 1,1, 1},
                                { 1, 1,-1,-1, 1,1, 1,-1,1,-1},
                                { 1, 1,-1, 1, 1,1, 1, 1,1, 1}};
    std::cout << sol.cherryPickup(grid) << std::endl;
    return 0;
}
