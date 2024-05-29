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

using namespace std;
/*
 * @lc app=leetcode.cn id=1052 lang=cpp
 *
 * [1052] 爱生气的书店老板
 */

// @lc code=start
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (grumpy[i] == 0) {
                result += customers[i];
            }
        }
        int j = std::min(n, minutes);
        int max = 0;
        for (int i = 0; i < j; i++) {
            if (grumpy[i] == 1) {
                max += customers[i];
            }
        }
        int acc = max;
        for (int i = 0; j < n; i++,j++) {
            if (grumpy[i] == 1) {
                acc -= customers[i];
            }
            if (grumpy[j] == 1) {
                acc += customers[j];
            }
            max = std::max(acc, max);
        }
        return result + max;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> customers = {1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0,1,0,1,0,1,0,1};
    std::cout << sol.maxSatisfied(customers, grumpy, 3) << std::endl;
    // vector<int> customers = {1};
    // vector<int> grumpy = {0};
    // std::cout << sol.maxSatisfied(customers, grumpy, 3) << std::endl;
    // vector<int> customers = {5,8};
    // vector<int> grumpy = {0,1};
    // std::cout << sol.maxSatisfied(customers, grumpy, 1) << std::endl;
    return 0;
}
