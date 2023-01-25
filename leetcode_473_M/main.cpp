#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

    bool helper(vector<int>& matchsticks, vector<int>& edges, int index, int target) {
        if (index >= matchsticks.size()) {
            return true;
        }
        for (int i = 0; i < edges.size(); i++) {
            edges[i] += matchsticks[index];
            if (edges[i] <= target && helper(matchsticks, edges, index + 1, target)) {
                return true;
            }
            edges[i] -= matchsticks[index];
        }
        return false;
    }

    bool makesquare(vector<int>& matchsticks) {
        int totalLength = 0;
        for (int num : matchsticks) {
            totalLength += num;
        }
        if (totalLength % 4 != 0) {
            return false;
        }
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        int target = totalLength / 4;
        vector<int> edges(4, 0);
        return helper(matchsticks, edges, 0, target);
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> q = {5,5,5,5,16,4,4,4,4,4,3,3,3,3,4};
    cout << sol.makesquare(q) << endl;
    return 0;
}
