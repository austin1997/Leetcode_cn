#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    bool pushDigit(int32_t &ret, int digit) {
        if (ret == 0 && digit == 0) {
            return true;
        }
        long tmp = 10 * (long)ret + digit;
        ret = (int32_t)tmp;
        return (tmp >> 31) == 0;
    }
    int myAtoi(string str) {
        int32_t ret = 0;
        bool started = false;
        bool positive = true;
        for (int i = 0; i < str.length(); ++i) {
            char ch = str[i];
            if (ch == ' ' && !started) {
                continue;
            }
            if (ch == '+' && !started) {
                started = true;
                continue;
            }
            if (ch == '-' && !started) {
                started = true;
                positive = false;
                continue;
            }
            if (ch >= '0' && ch <= '9') {
                started = true;
                bool success = pushDigit(ret, ch - '0');
                if (!success) {
                    if (positive) {
                        return INT32_MAX;
                    }else {
                        return INT32_MIN;
                    }
                }
                continue;
            }
            break;
        }        
        return positive ? ret : -ret;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    cout << sol.myAtoi("-2147483648") << endl;
    return 0;
}

