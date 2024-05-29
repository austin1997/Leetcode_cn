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

using namespace std;
/*
 * @lc app=leetcode.cn id=377 lang=cpp
 *
 * [377] 组合总和 Ⅳ
 */

// @lc code=start
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> results(target + 1);
        results[0] = 1;
        unordered_set<int> numsSet(nums.begin(), nums.end());
        for (int i = 1; i < results.size(); i++) {
            results[i] = 0;
            for (int j = 0; j <= i - 1; j++) {
                auto tmp = target - j;
                if (numsSet.count(tmp)) {
                    results[i] += results[j];
                }
            }
        }
        return results.back();
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> nums = {1, 2, 3};
    std::cout << sol.combinationSum4(nums, 4) << std::endl;
    return 0;
}
