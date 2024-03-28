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
 * @lc app=leetcode.cn id=1997 lang=cpp
 *
 * [1997] 访问完所有房间的第一天
 */

// @lc code=start
class Solution {
public:

    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        const static int mod = 1e9 + 7;
        vector<int64_t> dp(nextVisit.size(), 0);
        dp[1] = 2;
        for (int i = 2; i < nextVisit.size(); i++) {
            dp[i] = dp[i - 1] + 1 + (dp[i - 1] - dp[nextVisit[i - 1]] + mod) + 1;
            dp[i] %= mod;
        }
        return dp.back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    vector<int> q = {0,0,2};
    // vector<int> q = {0,0,0,0,0,0,0,0,0,9,1,8};
    Solution sol;
    std::cout << sol.firstDayBeenInAllRooms(q) << std::endl;
    return 0;
}
