#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <set>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> numsGame(vector<int>& nums) {
        int64_t mod = 1000000007;
        multiset<int> lower;
        multiset<int> upper;
        int64_t lowerSum = 0;
        int64_t upperSum = 0;
        lower.emplace(nums[0]);
        lowerSum += nums[0];
        vector<int> result(nums.size(), 0);
        for (int i = 1; i < nums.size(); i++) {
            nums[i] -= i;
            if (nums[i] > *lower.rbegin()) {
                upper.emplace(nums[i]);
                upperSum += nums[i];
                upperSum %= mod;
            } else {
                lower.emplace(nums[i]);
                lowerSum += nums[i];
                lowerSum %= mod;
            }
            if (lower.size() > upper.size() + 1) {
                upper.emplace(*lower.rbegin());
                upperSum += *lower.rbegin();
                upperSum %= mod;
                lowerSum -= *lower.rbegin();
                while (lowerSum < 0) {
                    lowerSum += mod;
                }
                lowerSum %= mod;
                lower.erase(std::prev(lower.end()));
            } else if (upper.size() > lower.size()) {
                lower.emplace(*upper.begin());
                lowerSum += *upper.begin();
                lowerSum %= mod;
                upperSum -= *upper.begin();
                while (upperSum < 0) {
                    upperSum += mod;
                }
                upperSum %= mod;
                upper.erase(upper.begin());
            }
            if ((i + 1) % 2 == 0) {
                result[i] = upperSum - lowerSum;
            } else {
                result[i] = upperSum - lowerSum + *lower.rbegin();
            }
            while (result[i] < 0) {
                result[i] += mod;
            }
            result[i] %= mod;
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> q = {3,4,5,1,6,7};
    auto tmp = sol.numsGame(q);
    std::cout << tmp.size() << std::endl;
    return 0;
}
