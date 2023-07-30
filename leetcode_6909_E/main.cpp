#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int result = 0;
        for (int l = 0; l < nums.size(); l++) {
            if (nums[l] % 2 != 0) {
                continue;
            }
            for (int r = l; r < nums.size(); r++) {
                int max = nums[r];
                bool valid = true;
                for (int i = l; i < r - 1; i++) {
                    max = std::max(max, nums[i]);
                    if (nums[i] % 2 == nums[i + 1] % 2) {
                        valid = false;
                        break;
                    }
                }
                if (max > threshold) {
                    valid = false;
                }
                if (valid) {
                    result = std::max(result, r - l + 1);
                }
            }
        }
        return result;
    }

};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<int> q1 = {2, 2};
    std::cout << sol.longestAlternatingSubarray(q1, 18) << std::endl;
}
