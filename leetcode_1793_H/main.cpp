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
 * @lc app=leetcode.cn id=1793 lang=cpp
 *
 * [1793] 好子数组的最大分数
 */

// @lc code=start
class Solution {
public:

    int buildTree(const vector<int>& nums, int lower, int upper, int index) {
        if (upper - lower <= 1) {
            tree[index] = nums[lower];
            return tree[index];
        }
        int mid = (lower + upper) / 2;
        auto left = buildTree(nums, lower, mid, index * 2);
        auto right = buildTree(nums, mid, upper, index * 2 + 1);
        tree[index] = std::min(left, right);
        return tree[index];
    }

    int queryTree(int qLower, int qUpper, int lower, int upper, int index) {
        if (qLower <= lower && upper <= qUpper) {
            return tree[index];
        }
        if (qUpper <= lower || upper <= qLower) {
            return std::numeric_limits<int>::max();
        }
        int mid = (lower + upper) / 2;
        auto left = queryTree(qLower, qUpper, lower, mid, index * 2);
        auto right = queryTree(qLower, qUpper, mid, upper, index * 2 + 1);
        return std::min(left, right);
    }

    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int i = k;
        int j = k;
        int base = nums[k];
        int result = base;
        while (i > 0 || j < n - 1) {
            int ii = i - 1;
            int jj = j + 1;
            if (ii >= 0 && jj < n) {
                if (nums[ii] >= nums[jj]) {
                    base = std::min(nums[ii], base);
                    result = std::max(base * (j - ii + 1), result);
                    i = ii;
                } else {
                    base = std::min(nums[jj], base);
                    result = std::max(base * (jj - i + 1), result);
                    j = jj;
                }
            } else if (ii >= 0) {
                base = std::min(nums[ii], base);
                result = std::max(base * (j - ii + 1), result);
                i = ii;
            } else {
                base = std::min(nums[jj], base);
                result = std::max(base * (jj - i + 1), result);
                j = jj;
            }
        }
        return result;
    }

    vector<int> tree;
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    std::vector<int> q = {1,4,3,7,4,5};
    std::cout << sol.maximumScore(q, 3) << std::endl;

    // std::vector<int> q = {5,5,4,5,4,1,1,1};
    // std::cout << sol.maximumScore(q, 0) << std::endl;
    return 0;
}
