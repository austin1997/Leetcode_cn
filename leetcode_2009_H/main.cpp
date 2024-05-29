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
#include <TreeNode.h>

using namespace std;
/*
 * @lc app=leetcode.cn id=2009 lang=cpp
 *
 * [2009] 使数组连续的最少操作数
 */

// @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> tmp(nums.begin(), nums.end());
        nums = vector<int>(tmp.begin(), tmp.end());
        std::sort(nums.begin(), nums.end());
        // vector<int> endIndex(nums.size(), nums.size() - 1);
        int currStart = 0;
        int result = n - 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= nums[currStart] + n) {
                auto endIndex = i;
                result = std::min(n - (endIndex - i), result);
                currStart++;
            }
        }
        if (currStart < nums.size()) {
            int endIndex = nums.size();
            result = std::min(n - (endIndex - currStart), result);
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // vector<int> q = {4, 2, 5, 3};
    vector<int> q = {1, 2, 3, 5, 6};
    cout << sol.minOperations(q) << endl;
    return 0;
}
