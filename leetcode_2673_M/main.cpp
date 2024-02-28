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
 * @lc app=leetcode.cn id=2673 lang=cpp
 *
 * [2673] 使二叉树所有路径值相等的最小代价
 */

// @lc code=start
class Solution {
public:

    int minIncrements(vector<int>& cost, int root) {
        auto leftIndex = root * 2;
        auto rightIndex = root * 2 + 1;
        if (leftIndex > cost.size()) {
            return 0;
        }
        auto result = minIncrements(cost, leftIndex);
        result += minIncrements(cost, rightIndex);
        auto& left = cost[leftIndex - 1];
        auto& right = cost[rightIndex - 1];
        if (left < right) {
            result += right - left;
            left = right;
        } else {
            result += left - right;
            right = left;
        }
        cost[root - 1] += left;
        return result;
    }

    int minIncrements(int n, vector<int>& cost) {
        return minIncrements(cost, 1);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::vector<int> q = {1,5,2,2,3,3,1};
    // std::cout << sol.minIncrements(7, q) << std::endl;

    std::vector<int> q = {764,1460,2664,764,2725,4556,5305,8829,5064,5929,7660,6321,4830,7055,3761};
    std::cout << sol.minIncrements(15, q) << std::endl;
    return 0;
}
