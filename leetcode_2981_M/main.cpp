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
 * @lc app=leetcode.cn id=2981 lang=cpp
 *
 * [2981] 找出出现至少三次的最长特殊子字符串 I
 */

// @lc code=start
class Solution {
public:
    int maximumLength(string s) {
        vector<map<int, int>> acc(26);
        auto prev = s[0] - 'a';
        int cnt = 1;
        for (int i = 1; i < s.length(); i++) {
            auto curr = s[i] - 'a';
            if (prev == curr) {
                cnt++;
            } else {
                acc[prev].emplace(cnt, 0).first->second++;
                prev = curr;
                cnt = 1;
            }
        }
        acc[prev].emplace(cnt, 0).first->second++;
        int result = 0;
        for (auto &item : acc) {
            while (!item.empty()) {
                auto iter = item.rbegin();
                if (iter->second >= 3) {
                    result = std::max(result, iter->first);
                    break;
                }
                if (iter->first > 1) {
                    item.emplace(iter->first - 1, 0).first->second += iter->second * 2;
                }
                item.erase(iter->first);
            }
        }
        if (result == 0) {
            return -1;
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // std::cout << sol.maximumLength("aaaa") << std::endl;
    // std::cout << sol.maximumLength("abcdef") << std::endl;
    // std::cout << sol.maximumLength("abcaba") << std::endl;
    std::cout << sol.maximumLength("abcccccdddd") << std::endl;
    return 0;
}
