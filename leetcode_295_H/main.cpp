#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <set>
#include <deque>
#include <queue>

using namespace std;

class MedianFinder {
public:
    MedianFinder() {

    }
    
    void addNum(int num) {
        if (lower.empty() || num <= lower.top()) {
            lower.emplace(num);
        } else {
            upper.emplace(num);
        }
        if (lower.size() > upper.size() + 1) {
            upper.emplace(lower.top());
            lower.pop();
        }
        if (upper.size() > lower.size()) {
            lower.emplace(upper.top());
            upper.pop();
        }
    }
    
    double findMedian() {
        if (lower.size() == upper.size()) {
            return (lower.top() + upper.top()) / 2.0;
        }
        return lower.top();
    }

    priority_queue<int> lower;
    priority_queue<int, vector<int>, std::greater<int>> upper;

};

int main(int argc, char const *argv[])
{
    MedianFinder sol;
    sol.addNum(1);
    sol.addNum(2);
    std::cout << sol.findMedian() << std::endl;
    sol.addNum(3);
    std::cout << sol.findMedian() << std::endl;
    return 0;
}
