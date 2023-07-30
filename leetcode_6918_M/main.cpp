#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>

using namespace std;

class Solution {
public:
    string merge(const string& a, const string& b) {
        if (a.find(b) != string::npos) {
            return a;
        }
        int minPos = a.length();
        for (int i = 1; i <= b.length(); i++) {
            auto sub = b.substr(0, i);
            auto pos = a.rfind(sub);
            if (pos != string::npos && pos + i == a.length() && pos < minPos) {
                minPos = pos;
            }
        }
        return a.substr(0, minPos) + b;
    }
    
    static bool select(const string& a, const string& b) {
        if (a.length() < b.length()) {
            return true;
        } else if (a.length() > b.length()) {
            return false;
        } else if (a < b) {
            return true;
        } else {
            return false;
        }
    }
    
    string minimumString(string a, string b, string c) {
        string ab = merge(a, b);
        string ba = merge(b, a);
        string ac = merge(a, c);
        string ca = merge(c, a);
        string bc = merge(b, c);
        string cb = merge(c, b);
        
        string ab_c = merge(ab, c);
        string ba_c = merge(ba, c);
        string ac_b = merge(ac, b);
        string ca_b = merge(ca, b);
        string bc_a = merge(bc, a);
        string cb_a = merge(cb, a);
        
        std::vector<string> vec = {ab_c, ba_c, ac_b, ca_b, bc_a, cb_a};
        std::sort(vec.begin(), vec.end(), select);
        return vec.front();
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::cout << sol.minimumString("aba", "c", "b") << std::endl;
}
