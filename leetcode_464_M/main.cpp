#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<int, bool> map;
    bool canIWin(int used, int maxChoosableInteger, int remainTotal) {
        auto iter = map.find(used);
        if (iter != map.end()) {
            return iter->second;
        }
        bool result = false;
        for (int i = 0; i < maxChoosableInteger; i++) {
            if ((used & (1 << i)) == 0) {
                if (i + 1 >= remainTotal) {
                    result = true;
                    break;
                }
                bool next = canIWin(used | (1 << i), maxChoosableInteger, remainTotal - i - 1);
                if (!next) {
                    result = true;
                    break;
                }
            }
        }
        map.emplace(used, result);
        return result;
    }

    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal) {
            return false;
        }
        return canIWin(0, maxChoosableInteger, desiredTotal);
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    auto tmp = sol.canIWin(11, 25);
    cout << tmp << endl;
    return 0;
}
