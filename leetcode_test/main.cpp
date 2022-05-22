#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        return std::max(helper2(answerKey, k, 'T'), helper2(answerKey, k, 'F'));
        // return std::max(helper(answerKey, k, 'T'), helper(answerKey, k, 'F'));
    }

    int helper2(string answerKey, int k, char major) {
        int i = 0;
        int result = 0;
        for (int j = 0; j < answerKey.length(); j++) {
            if (answerKey[j] != major) {
                if (k > 0) {
                    k--;
                } else {
                    while(answerKey[i] == major) {
                        i++;
                    }
                    i++;
                }
            }
            result = std::max(result, j - i + 1);
        }
        return result;
    }

    int helper(string answerKey, int k, char major) {
        vector<int> prev(k + 1, 0);
        vector<int> next(k + 1);
        int result = 0;
        for (int i = 1; i <= answerKey.length(); i++) {
            char current = answerKey[i - 1];
            if (current == major) {
                for (int j = 0; j <= k; j++) {
                    next[j] = prev[j] + 1;
                    result = std::max(result, next[j]);
                }
            } else {
                next[0] = 0;
                for (int j = 1; j <= k; j++) {
                    next[j] = prev[j - 1] + 1;
                    result = std::max(result, next[j]);
                }
            }
            prev.swap(next);
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
//    cout << sol.maxConsecutiveAnswers("TTFF", 2) << endl;
    cout << sol.maxConsecutiveAnswers("FFTFTTTFFF", 1) << endl;
    return 0;
}
