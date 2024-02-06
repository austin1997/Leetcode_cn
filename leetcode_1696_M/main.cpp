#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <set>
#include <deque>

using namespace std;

/*
 * @lc app=leetcode.cn id=1696 lang=cpp
 *
 * [1696] 跳跃游戏 VI
 */

// @lc code=start
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        vector<int> dp;
        deque<int> sorted;
        dp.emplace_back(nums[0]);
        sorted.emplace_back(0);
        int index = 1;
        for (; index < nums.size(); index++) {
            while (!sorted.empty() && index - sorted.front() > k) {
                sorted.pop_front();
            }
            dp.emplace_back(dp[sorted.front()] + nums[index]);
            while (!sorted.empty() && dp[sorted.back()] <= dp.back()) {
                sorted.pop_back();
            }
            sorted.emplace_back(index);
        }
        return dp.back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> q = {40,30,-100,-100,-10,-7,-3,-3};
    std::cout << sol.maxResult(q, 2) << std::endl;
    return 0;
}
