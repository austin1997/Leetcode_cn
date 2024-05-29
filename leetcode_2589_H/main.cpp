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
 * @lc app=leetcode.cn id=2589 lang=cpp
 *
 * [2589] 完成所有任务的最少时间
 */

// @lc code=start
class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        std::sort(tasks.begin(), tasks.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
        });
        vector<int> usage(tasks.back()[1] + 1, 0);
        for (auto &task : tasks) {
            auto exist = std::accumulate(usage.begin() + task[0], usage.begin() + task[1] + 1, 0);
            if (exist >= task[2]) {
                continue;
            }
            auto diff = task[2] - exist;
            for (int i = task[1]; diff > 0 && i >= task[0]; i--) {
                if (usage[i] == 0) {
                    diff--;
                    usage[i] = 1;
                }
            }
        }
        return std::accumulate(usage.begin(), usage.end(), 0);
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<std::vector<int>> q = {{2, 3, 1}, {4, 5, 1}, {1, 5, 2}};
    std::cout << sol.findMinimumTime(q) << std::endl;
    return 0;
}
