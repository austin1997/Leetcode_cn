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
 * @lc app=leetcode.cn id=1969 lang=cpp
 *
 * [1969] 数组元素的最小非零乘积
 */

// @lc code=start
class Solution {
public:
    int64_t pow(int64_t base, int64_t power) {
        const int mod = 1e9 + 7;
        if (power < 1) {
            return 1;
        }
        if (power == 1) {
            return base;
        }

        auto mid = power / 2;
        auto result = this->pow(base, mid);
        result *= result;
        result %= mod;
        if (mid * 2 != power) {
            result *= base;
            result %= mod;
        }
        return result;
    }

    int minNonZeroProduct(int p) {
        int64_t cnt = 1;
        cnt = cnt << (p - 1);
        int64_t base = 1;
        base = (base << p) - 2;
        int64_t result = 1;
        const int mod = 1e9 + 7;
        result = pow(base % mod, cnt - 1);
        result *= (base + 1) % mod;
        result %= mod;
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    std::cout << sol.minNonZeroProduct(33) << std::endl;

    // std::vector<int> q = {5,5,4,5,4,1,1,1};
    // std::cout << sol.maximumScore(q, 0) << std::endl;
    return 0;
}
