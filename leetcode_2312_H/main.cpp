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
 * @lc app=leetcode.cn id=2312 lang=cpp
 *
 * [2312] 卖木头块
 */

// @lc code=start
class Solution {
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        unordered_map<int, int> basics;
        for (auto &price : prices) {
            basics.emplace(price[0] * 1000 + price[1], price[2]);
        }
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                auto iter = basics.find(i * 1000 + j);
                if (iter != basics.end()) {
                    dp[i][j] = iter->second;
                }
                for (int k = 1; k <= i / 2; k++) {
                    dp[i][j] = std::max(dp[k][j] + dp[i - k][j], dp[i][j]);
                }
                for (int k = 1; k <= j / 2; k++) {
                    dp[i][j] = std::max(dp[i][k] + dp[i][j - k], dp[i][j]);
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
    // std::vector<vector<int>> q = {{1,4,2},{2,2,7},{2,1,3}};
    // std::cout << sol.sellingWood(3, 5, q) << std::endl;

    std::vector<vector<int>> q = {{3, 2, 10},{1, 4, 2},{4, 1, 3}};
    std::cout << sol.sellingWood(4, 6, q) << std::endl;
    return 0;
}
