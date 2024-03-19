#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

/*
 * @lc app=leetcode.cn id=2834 lang=cpp
 *
 * [2834] 找出美丽数组的最小和
 */

// @lc code=start
class Solution {
public:
    uint64_t sum(uint64_t a, uint64_t b, uint64_t h) {
        return (a + b) * h / 2;
    }

    int minimumPossibleSum(int n, int target) {
        const uint64_t tmp = 1e9 + 7;
        int half = target / 2;
        if (n <= half) {
            return sum(1, n, n) % tmp;
        }
        uint64_t result = sum(1, half, half);
        
        int left = n - half;
        auto result1 = sum(target, target + left - 1, left);
        return (result % tmp + result1 % tmp) % tmp;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    std::cout << sol.minimumPossibleSum(3, 3) << std::endl;
    int tmp = 1e9;
    std::cout << sol.minimumPossibleSum(tmp, tmp) << std::endl;
    std::cout << sol.minimumPossibleSum(13, 50) << std::endl;

    return 0;
}
