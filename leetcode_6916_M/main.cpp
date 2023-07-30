#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        std::vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int p = 2; p * p <= n; p++) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i] = false;
                }
            }
        }
        std::unordered_set<int> primes;
        for (int i = 2; i < is_prime.size(); i++) {
            if (is_prime[i]) {
                primes.emplace(i);
            }
        }
        std::vector<std::vector<int>> result;
        for (int i = 2; i <= n / 2; i++) {
            if (primes.count(n - i)) {
                std::vector<int> tmp = {i, n - i};
                result.emplace_back(tmp);
            }
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    std::cout << sol.findPrimePairs(9).size() << std::endl;
}
