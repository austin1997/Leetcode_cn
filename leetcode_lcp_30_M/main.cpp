#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

class Solution {
public:
    int magicTower(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> negativeNums;
        vector<int> remains;
        int64_t sum = 1;
        int result = 0;
        for (auto num : nums) {
            if (num < 0) {
                negativeNums.emplace(num);
            }
            sum += num;
            while (sum <= 0) {
                if (negativeNums.empty()) {
                    return -1;
                }
                auto popNum = negativeNums.top();
                negativeNums.pop();
                sum -= popNum;
                remains.emplace_back(popNum);
                result++;
            }
        }
        for (auto num : remains) {
            sum += num;
        }
        if (sum <= 0) {
            return -1;
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    // vector<int> q = {100,100,100,-250,-60,-140,-50,-50,100,150};
    vector<int> q = {-200,-300,400,0};
    std::cout << sol.magicTower(q) << std::endl;
    return 0;
}
