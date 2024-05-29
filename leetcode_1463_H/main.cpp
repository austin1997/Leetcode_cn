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
 * @lc app=leetcode.cn id=1463 lang=cpp
 *
 * [1463] 摘樱桃 II
 */

// @lc code=start
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid.front().size();
        int dp[rows][cols][cols];
        dp[0][0][cols - 1] = grid[0][0] + grid[0][cols - 1];
        for (int i = 1; i < rows; i++) {
            for (int j1 = 0; j1 < cols && j1 <= i; j1++) {
                for (int k = 0; k < cols && k <= i; k++) {
                    int j2 = cols - 1 - k;
                    int best = 0;
                    // j1 - 1
                    if (0 <= j1 - 1 && j1 - 1 <= i - 1) {
                        // j2 - 1
                        if (k + 1 <= i - 1 && j2 - 1 >= 0) {
                            best = std::max(dp[i - 1][j1 - 1][j2 - 1], best);
                        }
                        // j2
                        if (k <= i - 1 && j2 < cols) {
                            best = std::max(dp[i - 1][j1 - 1][j2], best);
                        }
                        // j2 + 1
                        if (k - 1 <= i - 1 && j2 + 1 < cols) {
                            best = std::max(dp[i - 1][j1 - 1][j2 + 1], best);
                        }
                    }

                    // j1
                    if (0 <= j1 && j1 <= i - 1) {
                        // j2 - 1
                        if (k + 1 <= i - 1 && j2 - 1 >= 0) {
                            best = std::max(dp[i - 1][j1][j2 - 1], best);
                        }
                        // j2
                        if (k <= i - 1 && j2 < cols) {
                            best = std::max(dp[i - 1][j1][j2], best);
                        }
                        // j2 + 1
                        if (k - 1 <= i - 1 && j2 + 1 < cols) {
                            best = std::max(dp[i - 1][j1][j2 + 1], best);
                        }
                    }

                    // j1 + 1
                    if (j1 + 1 < cols && j1 + 1 <= i - 1) {
                        // j2 - 1
                        if (k + 1 <= i - 1 && j2 - 1 >= 0) {
                            best = std::max(dp[i - 1][j1 + 1][j2 - 1], best);
                        }
                        // j2
                        if (k <= i - 1 && j2 < cols) {
                            best = std::max(dp[i - 1][j1 + 1][j2], best);
                        }
                        // j2 + 1
                        if (k - 1 <= i - 1 && j2 + 1 < cols) {
                            best = std::max(dp[i - 1][j1 + 1][j2 + 1], best);
                        }
                    }
                    best += grid[i][j1];
                    if (j1 != j2) {
                        best += grid[i][j2];
                    }
                    dp[i][j1][j2] = best;
                }
            }
        }
        int result = 0;
        for (int j1 = 0; j1 < cols && j1 <= rows - 1; j1++) {
            for (int k = 0; k < cols && k <= rows - 1; k++) {
                int j2 = cols - 1 - k;
                result = std::max(dp[rows - 1][j1][j2], result);
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // vector<vector<int>> grid = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}};
    // vector<vector<int>> grid = {{1,0,0,0,0,0,1},
    //                             {2,0,0,0,0,3,0},
    //                             {2,0,9,0,0,0,0},
    //                             {0,3,0,5,4,0,0},
    //                             {1,0,2,3,0,0,6}};
    vector<vector<int>> grid = {{8,8,10,9,1,7},
                                {8,8,1,8,4,7},
                                {8,6,10,3,7,7},
                                {3,0,9,3,2,7},
                                {6,8,9,4,2,5},
                                {1,1,5,8,8,1},
                                {5,6,5,2,9,9},
                                {4,4,6,2,5,4},
                                {4,4,5,3,1,6},
                                {9,2,2,1,9,3}};
    std::cout << sol.cherryPickup(grid) << std::endl;
    return 0;
}
