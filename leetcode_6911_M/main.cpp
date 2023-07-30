#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>

using namespace std;

class Solution {
public:
    long long helper(int n) {
        long long result = 1L;
        for (int i = n; i > 0; i--) {
            result *= i;
        }
        return result;
    }
    
    long long continuousSubarrays(vector<int>& nums) {
        long long result = 0L;
        std::multimap<int, int> value_index;
        for (int i = 0; i < nums.size(); i++) {
            value_index.emplace(nums[i], i);
            int min = value_index.begin()->first;
            int max = value_index.rbegin()->first;
            if (std::abs(min - max) > 2) {
                int old_length = value_index.size() - 1;
                result += helper(old_length);
                if (min == nums[i]) {
                    int target_value = min + 2;
                    auto upperbound = value_index.upper_bound(target_value);
                    value_index.erase(upperbound, value_index.end());
                } else {
                    int target_value = max - 2;
                    auto lowerbound = value_index.lower_bound(target_value);
                    value_index.erase(value_index.begin(), lowerbound);
                }
                result -= helper(value_index.size() - 1);
            }
        }
        result += helper(value_index.size());
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<int> q1 = {5,4,2,4};
    std::cout << sol.continuousSubarrays(q1) << std::endl;
}
