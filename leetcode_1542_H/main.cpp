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
 * @lc app=leetcode.cn id=1542 lang=cpp
 *
 * [1542] 找出最长的超赞子字符串
 */

// @lc code=start
class Solution {
public:
    int longestAwesome(string s) {
        int n = s.length();
        unordered_map<int, int> prefix;
        prefix.emplace(0, -1);
        int acc = 0;
        int result = 1;
        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';
            acc ^= (1 << d);
            auto iter = prefix.emplace(acc, i);
            result = std::max(i - iter.first->second, result);
            for (int j = 0; j < 10; j++) {
                auto tmp = acc ^ (1 << j);
                auto iter = prefix.find(tmp);
                if (iter != prefix.end()) {
                    result = std::max(i - iter->second, result);
                }
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    std::cout << sol.longestAwesome("3242415") << std::endl;
    std::cout << sol.longestAwesome("12345678") << std::endl;
    std::cout << sol.longestAwesome("213123") << std::endl;
    std::cout << sol.longestAwesome("00") << std::endl;
    return 0;
}
