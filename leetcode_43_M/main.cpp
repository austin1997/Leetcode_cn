#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void add(string& num1, string& num2) {
        if (num1.length() < num2.length()) {
            swap(num1, num2);
        }
        int carry = 0;
        for (int i = 0; i < num1.length(); i++) {
            int val1 = num1[num1.length() - 1 - i] - '0';
            int val2 = 0;
            if (i < num2.length()) {
                val2 = num2[num2.length() - i - 1] - '0';
            }
            val1 += val2 + carry;
            num1[num1.length() - i - 1] = val1 % 10 + '0';
            carry = val1 / 10;
        }
        if (carry > 0) {
            num1.insert(0, 1, carry + '0');
        }
    }

    string multiply(const string& num1, int num2) {
        string result;
        int carry = 0;
        for (int i = 0; i < num1.length(); i++) {
            int val = num1[num1.length() - 1 - i] - '0';
            val = val * num2 + carry;
            result.push_back(val % 10 + '0');
            carry = val / 10;
        }
        if (carry > 0) {
            result.push_back(carry + '0');
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string multiply(string num1, string num2) {
        string result = "0";
        if (num1.length() < num2.length()) {
            swap(num1, num2);
        }
        for (int i = 0; i < num2.length(); i++) {
            string tmp = multiply(num1, num2[num2.length() - i - 1]);
            for (int j = 0; j < i; j++) {
                tmp.push_back('0');
            }
            add(result, tmp);
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    cout << sol.multiply("2", "3") << endl;
    return 0;
}
