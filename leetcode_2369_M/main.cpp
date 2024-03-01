#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=2369 lang=cpp
 *
 * [2369] 检查数组是否存在有效划分
 */

// @lc code=start
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        if (nums.size() < 2) {
            return false;
        }
        vector<bool> dp(nums.size(), false);
        dp[0] = false;
        if (nums.size() > 1 && nums[0] == nums[1]) {
            dp[1] = true;
        }
        if (nums.size() < 3) {
            return dp.back();
        }
        if ((nums[0] == nums[1] && nums[1] == nums[2]) || 
            (nums[0] == nums[1] - 1 && nums[0] == nums[2] - 2)) {
            dp[2] = true;
        }
        for (int i = 3; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] && dp[i - 2]) {
                dp[i] = true;
                continue;
            }
            if (nums[i] == nums[i - 1] && nums[i] == nums[i - 2] && dp[i - 3]) {
                dp[i] = true;
                continue;
            }
            if (nums[i] == nums[i - 1] + 1 && nums[i] == nums[i - 2] + 2 && dp[i - 3]) {
                dp[i] = true;
                continue;
            }
        }
        return dp.back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    // std::vector<int> in1 = {4, 4, 4, 5, 6};
    // std::cout << sol.validPartition(in1) << std::endl;

    std::vector<int> in1 = {1, 1, 1, 2};
    std::cout << sol.validPartition(in1) << std::endl;

    return 0;
}
