#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> result;
        map<int, int> edges;
        edges.emplace(0, 0);
        int prev = 0;
        for (auto& entry : positions) {
            int height = entry[1];
            int left = entry[0];
            int right = left + height;
            auto prevEdge = edges.upper_bound(left);
            prevEdge--;
            auto lastEdge = edges.lower_bound(right);
            int out = prevEdge->second;
            for (auto iter = prevEdge; iter != lastEdge; iter++) {
                out = max(out, iter->second);
            }
            lastEdge--;
            int original = lastEdge->second;
            out += height;
            edges.erase(edges.lower_bound(left), edges.lower_bound(right));
            edges[left] = out;
            edges.emplace(right, original);
            prev = max(prev, out);
            result.emplace_back(prev);
        }

        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
//    vector<vector<int>> q1 = {{1,2},{2,3},{6,1}};
//    vector<vector<int>> q1 = {{2,1},{2,9},{1,8}};
    vector<vector<int>> q1 = {{9,6},{2,2},{2,6}};
    auto tmp = sol.fallingSquares(q1);
    for (auto num : tmp) {
        cout << num << ", ";
    }
    return 0;
}
