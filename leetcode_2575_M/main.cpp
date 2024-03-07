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
 * @lc app=leetcode.cn id=2575 lang=cpp
 *
 * [2575] 找出字符串的可整除数组
 */

// @lc code=start
class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        vector<int> result(word.size(), 0);
        int64_t tmp = 0;
        for (int i = 0; i < word.size(); i++) {
            auto ch = word[i];
            int64_t val = ch - '0';
            tmp = 10 * tmp + val;
            tmp = tmp % m;
            if (tmp == 0) {
                result[i] = 1;
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;

    // std::vector<vector<int>> in1 = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
    // std::cout << sol.countPaths(7, in1) << std::endl;

    std::vector<vector<int>> in1 = {{1,0,10}};
    std::cout << sol.countPaths(2, in1) << std::endl;

    return 0;
}
