#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    bool canReorderDoubled(vector<int> &arr) {
        multiset<int> set(arr.begin(), arr.end());
        while (!set.empty()) {
            int least = *set.begin();
            set.erase(set.begin());
            if (least < 0) {
                auto iter = set.find(least / 2);
                if (iter == set.end() || *iter * 2 != least) {
                    return false;
                }
                set.erase(iter);
            } else {
                auto iter = set.find(least * 2);
                if (iter == set.end()) {
                    return false;
                }
                set.erase(iter);
            }
        }
        return true;
    }

    bool canReorderDoubled1(vector<int> &arr) {
        std::sort(arr.begin(), arr.end());
        auto iter = std::upper_bound(arr.begin(), arr.end(), -1);
        int index = iter - arr.begin();
        for (int i = 0; i < (arr.size() - index) / 2; i++) {
            int tmp = i + index;
            int tmp2 = i + (arr.size() + index) / 2;
            if (tmp2 >= arr.size() || arr[tmp2] != 2 * arr[tmp]) {
                return false;
            }
        }
        for (int i = 0; i < index / 2; i++) {
            if (index / 2 + i >= index || 2 * arr[index / 2 + i] != arr[i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
//    vector<int> input = {4,-2,2,-4};
    vector<int> input = {2, 4, 0, 0, 8, 1};
    cout << sol.canReorderDoubled(input) << endl;
    return 0;
}
