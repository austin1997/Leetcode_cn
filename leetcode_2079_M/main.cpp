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
 * @lc app=leetcode.cn id=2079 lang=cpp
 *
 * [2079] 给植物浇水
 */

// @lc code=start
class Solution {
public:
    int helper(const vector<int>& plants, int capacity, int startIndex) {
        int lastIndex;
        int n = plants.size();
        int acc = 0;
        for (lastIndex = startIndex; lastIndex < n && acc <= capacity; lastIndex++) {
            acc += plants[lastIndex];
            if (acc > capacity) {
                return lastIndex;
            }
        }
        return lastIndex;
    }

    int wateringPlants(vector<int>& plants, int capacity) {
        int startIndex = 0;
        int n = plants.size();
        int result = 0;
        while (startIndex < n) {
            auto lastIndex = helper(plants, capacity, startIndex);
            startIndex = lastIndex;
            if (startIndex < n) {
                result += lastIndex * 2;
            } else {
                result += lastIndex;
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<int> q = {2, 2, 3, 3};
    std::cout << sol.wateringPlants(q, 5) << std::endl;
    return 0;
}
