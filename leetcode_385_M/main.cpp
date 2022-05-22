#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class NestedInteger {
public:
    // Constructor initializes an empty nested list.
    NestedInteger() = default;

    // Constructor initializes a single integer.
    NestedInteger(int value) : isList(false), value(value) {}

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const {
        return !isList;
    }

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const {
        return value;
    }

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value) {
        this->isList = false;
        this->value = value;
    }

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni) {
        this->list.emplace_back(ni);
    }

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const {
        return this->list;
    }

private:
    bool isList = true;
    int value = 0;
    vector<NestedInteger> list;
};

class Solution {
public:
    NestedInteger deserialize(string s) {
        char *next;
        return helper(s.c_str(), &s[s.length() - 1] + 1, &next);
    }

    NestedInteger helper(const char* start, const char *end, char **next) {
        if (start == end) {
            return {};
        }
        NestedInteger result;
        if (*start == ']') {
            *next = const_cast<char*>(start);
        } else if (*start != '[') {
            int num = strtol(start, next, 10);
            result.setInteger(num);
        } else {
            *next = const_cast<char*>(start);
            if (*(*next + 1) == ']') {
                *next = *next + 2;
                return result;
            }
            while (**next != ']') {
                result.add(helper(*next + 1, end, next));
            }
            *next += sizeof(char);
        }
        // ','
        return result;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
    auto ans = sol.deserialize("[123,456,[788,799,833],[[]],10,[]]");
    cout << ans.getInteger() << endl;
    return 0;
}
