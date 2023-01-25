#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class RangeModule {
public:
    RangeModule() {

    }

    void addRange(int left, int right) {
        if (left == right) {
            return;
        }
        auto iter = range.upper_bound(left);
        if (iter == range.begin()) {
            iter = range.emplace(left, right - left).first;
        } else {
            iter--;
        }
        int old_right = iter->first + iter->second;
        if (left > old_right) {
            range.emplace(left, right - left);
            return;
        }
        int max = std::max(right, old_right);
        auto nextIter = next(iter, 1);
        while (nextIter != range.end() && nextIter->first <= max) {
            max = std::max(max, nextIter->first + nextIter->second);
            range.erase(nextIter);
            nextIter = next(iter, 1);
        }
        iter->second = max - iter->first;
    }

    bool queryRange(int left, int right) {
        auto iter = range.upper_bound(left);
        if (iter == range.begin()) {
            return false;
        }
        iter--;
        int max = iter->first + iter->second;
        return max >= right;
    }

    void removeRange(int left, int right) {
        if (range.empty()) {
            return;
        }
        auto iter = range.upper_bound(left);
//        if (iter == range.begin()) {
//            return;
//        }
        iter--;
        while (iter != range.end() && iter->first < right) {
            int end = iter->first + iter->second;
            int len = iter->second;
            if (end < right) {
                len = left - iter->first;
            } else {
                len = end - right;
                if (len > 0) {
                    range.emplace(right, len);
                }
                len = left - iter->first;
            }
            if (len <= 0) {
                auto tmp = iter;
                iter = std::next(iter, 1);
                range.erase(tmp);
            } else {
                iter->second = len;
                iter = std::next(iter, 1);
            }
        }

    }

    map<int, int> range;
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

int main(int argc, char const *argv[])
{
    // ["queryRange","queryRange","addRange","removeRange"]
    //[[8,9],[6,9],[2,3],[1,8]]
    RangeModule obj;
    obj.removeRange(4, 8);
    obj.addRange(1, 10);
    cout << obj.queryRange(1, 7) << endl;
    obj.addRange(2, 3);
    obj.removeRange(2, 3);
    cout << obj.queryRange(8, 9) << endl;
    cout << obj.queryRange(6, 9) << endl;
    obj.addRange(2, 3);
    obj.removeRange(1, 8);
    return 0;
}
