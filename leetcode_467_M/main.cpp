#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

class Solution {
public:
    void record(char start, int length) {
        for (int i = 0; i < 26 && length > 0; i++, length--) {
            int index = (start + i - 'a') % 26;
            count[index] = max(count[index], length);
        }
    }

    int findSubstringInWraproundString(string p) {
        count = vector<int>(26, 0);
        char start = p[0];
        int i = 0;
        int j = 1;
        while (j < p.length()) {
            char curr = p[j];
            char prev = p[j - 1];
            if (curr - prev == 1 || prev == 'z' && curr == 'a') {
                j++;
                continue;
            }
            record(start, j - i);
            i = j;
            j++;
            start = p[i];
        }
        record(start, j - i);
        int result = 0;
        for (auto num : count) {
            result += num;
        }
        return result;
    }

    vector<int> count;
};

int main(int argc, char const *argv[])
{
    Solution sol;
    auto tmp = sol.findSubstringInWraproundString("cac");
    cout << tmp << endl;
    return 0;
}
