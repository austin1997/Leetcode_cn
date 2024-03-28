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
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 */

// @lc code=start
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> results(amount + 1, 0);
        results[0] = 1;
        for (auto value : coins) {
            for (int i = 0; i < results.size(); i++) {
                if (i + value <= amount) {
                    results[i + value] += results[i];
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
    vector<int> q = {1, 2, 5};
    std::cout << sol.change(5, q) << std::endl;
    return 0;
}
