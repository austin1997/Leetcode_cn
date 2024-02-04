#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution
{
public:
    int stoneGameVI(vector<int> &aliceValues, vector<int> &bobValues)
    {
        auto sum = aliceValues;
        for (auto i = 0; i < aliceValues.size(); ++i)
        {
            sum[i] += bobValues[i];
        }
        auto indices = sum;
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&sum](auto a, auto b) {
            return sum[a] > sum[b];
        });
        int aliceResult = 0;
        int bobResult = 0;
        for (int i = 0; i < indices.size(); ++i)
        {   
            if (i % 2 == 0)
            {
                aliceResult += aliceValues[indices[i]];
            }
            else
            {
                bobResult += bobValues[indices[i]];
            }
        }
        if (aliceResult > bobResult)
        {
            return 1;
        }
        else if (aliceResult < bobResult)
        {
            return -1;
        }
        return 0;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<int> aliceValues = {1, 3};
    std::vector<int> bobValues = {2, 1};
    std::cout << sol.stoneGameVI(aliceValues, bobValues) << std::endl;
    return 0;
}
