#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/*
 * @lc app=leetcode.cn id=1690 lang=cpp
 *
 * [1690] 石子游戏 VII
 */

// @lc code=start
class Solution {
public:
    int aliceHelper(const vector<int> &stones, int i, int j) {
        auto remainingCnt = j - i + 1;
        if (remainingCnt <= 1) {
            return 0;
        }

        if (dp[i][j] >= 0) {
            return dp[i][j];
        }

        int left = bobHelper(stones, i + 1, j);
        int right = bobHelper(stones, i, j - 1);
        dp[i][j] = std::max(left, right);
        return dp[i][j];
    }

    int bobHelper(const vector<int> &stones, int i, int j) {
        auto remainingCnt = j - i + 1;
        if (remainingCnt <= 0) {
            return 0;
        }
        if (remainingCnt == 1) {
            return stones[i];
        }
        if (dp[i][j] >= 0) {
            return dp[i][j];
        }
        int left = stones[i] + aliceHelper(stones, i + 1, j);
        int right = stones[j] + aliceHelper(stones, i, j - 1);
        dp[i][j] = std::min(left, right);
        return dp[i][j];
    }

    int stoneGameVII(vector<int>& stones) {
        dp = vector<vector<int>>(stones.size(), vector<int>(stones.size(), -1));
        return aliceHelper(stones, 0, stones.size() - 1);
    }

    vector<vector<int>> dp;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::vector<int> stones = {5,3,1,4,2};
    std::vector<int> stones = {7,90,5,1,100,10,10,2};
    std::cout << sol.stoneGameVII(stones) << std::endl;
    return 0;
}
