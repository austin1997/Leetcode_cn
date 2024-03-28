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
 * @lc app=leetcode.cn id=2580 lang=cpp
 *
 * [2580] 统计将重叠区间合并成组的方案数
 */

// @lc code=start
class Solution {
public:
    int64_t pow(int64_t base, int64_t exp) {
        const int64_t mod = 1e9 + 7;
        if (exp <= 0) {
            return 1;
        }
        if (exp == 1) {
            return base;
        }
        auto tmp = pow(base, exp / 2);
        tmp = (tmp * tmp) % mod;
        if (exp % 2 != 0) {
            tmp = (tmp * base) % mod;   
        }
        return tmp;
    }

    int countWays(vector<vector<int>>& ranges) {
        std::sort(ranges.begin(), ranges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a.front() < b.front(); 
        });

        int end = -1;
        auto groupCnt = 0;
        for (const auto& range : ranges) {
            if (range.front() > end) {
                groupCnt++;
            }
            end = std::max(range.back(), end);
        }
        
        return pow(2, groupCnt);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    // vector<vector<int>> q = {{6, 10}, {5, 15}};
    vector<vector<int>> q = {{1,3},{10,20},{2,5},{4,8}};
    Solution sol;
    std::cout << sol.countWays(q) << std::endl;
    return 0;
}
