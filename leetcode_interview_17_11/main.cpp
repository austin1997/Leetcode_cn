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
    int findClosest(vector<string>& words, string word1, string word2) {
        set<int> map1;
        set<int> map2;

        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                map1.emplace(i);
            } else if (words[i] == word2) {
                map2.emplace(i);
            }
        }

        int result = 0;
        for (auto index1 : map1) {
            auto lb = map2.lower_bound(index1);
            if (lb != map2.end()) {
                result = min(result, abs(index1 - *lb));
            }
            if (lb != map2.begin()) {
                lb--;
                result = min(result, abs(index1 - *lb));
            }
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::vector<string> q1 = {"I","am","a","student","from","a","university","in","a","city"};
    auto tmp = sol.findClosest(q1, "a", "student");
    cout << tmp << endl;
    return 0;
}
