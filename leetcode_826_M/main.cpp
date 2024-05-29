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
 * @lc app=leetcode.cn id=826 lang=cpp
 *
 * [826] 安排工作以达到最大收益
 */

// @lc code=start
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        int m = worker.size();
        vector<int> maxProfit(1e5 + 1, 0);
        for (int i = 0; i < n; i++) {
            maxProfit[difficulty[i]] = std::max(profit[i], maxProfit[difficulty[i]]);
        }
        for (int i = 1; i < maxProfit.size(); i++) {
            maxProfit[i] = std::max(maxProfit[i - 1], maxProfit[i]);
        }
        int result = 0;
        for (int i = 0; i < m; i++) {
            result += maxProfit[worker[i]];
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::vector<int> d = {2, 4, 6, 8, 10};
    // std::vector<int> p = {10,20,30,40,50};
    // std::vector<int> w = {4,5,6,7};
    std::vector<int> d = {66,1,28,73,53,35,45,60,100,44,59,94,27,88,7,18,83,18,72,63};
    std::vector<int> p = {66,20,84,81,56,40,37,82,53,45,43,96,67,27,12,54,98,19,47,77};
    std::vector<int> w = {61,33,68,38,63,45,1,10,53,23,66,70,14,51,94,18,28,78,100,16};
    std::cout << sol.maxProfitAssignment(d, p, w) << std::endl;
    return 0;
}
