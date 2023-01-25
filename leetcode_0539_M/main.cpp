#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.size() >= 1440) {
            return 0;
        }
        vector<int> times(timePoints.size());
        for (int i = 0; i < timePoints.size(); i++) {
            times[i] = helper(timePoints[i]);
        }
        std::sort(times.begin(), times.end());
        int min = 1440;
        for (int i = 1; i < times.size(); i++) {
            min = std::min(times[i] - times[i - 1], min);
        }
        for (int i = 0; i < times.size() && times[i] < 720; i++) {
            times[i] += 1440;
        }
        std::sort(times.begin(), times.end());
        for (int i = 1; i < times.size(); i++) {
            min = std::min(times[i] - times[i - 1], min);
        }
        return min;
    }

    int helper(const string& str) {
        int hh = (str[0] - '0') * 10 + (str[1] - '0');
        int mm = (str[3] - '0') * 10 + (str[4] - '0');
        return hh * 60 + mm;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<string> board1 = {"01:01", "02:01"};
    cout << sol.findMinDifference(board1) << endl;
    return 0;
}
