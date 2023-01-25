#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>

using namespace std;

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) {
            return true;
        }
        if (!shouldVisit(sx, sy, tx, ty)) {
            return false;
        }
        if (tx < ty) {
            return reachingPoints(sx, sy, tx, ty - tx);
        } else {
            return reachingPoints(sx, sy, tx - ty, ty);
        }
    }

    bool shouldVisit(int x, int y, int tx, int ty) {
        if (max(x, y) > max(tx, ty) || min(x, y) > min(tx, ty) || min(x, y) > abs(tx - ty)) {
            return false;
        }

        return true;
    }
};


int func(int n)

{
    static int x = 0;
    if(n<=0)
        return 0;
    x++;
    return func(n-1) + x;
}

void foo(int n, int sum)

{
    if(n==0) return;
    int k = n%10;
    int j = n/10;
    sum = sum + k;
    foo(j, sum);
    cout << k << ", ";
}

int main(int argc, char const *argv[]) {
    Solution sol;
    auto tmp = sol.reachingPoints(1, 1, 3, 5);
//    auto tmp = sol.reachingPoints(1, 1, 2, 2);
//    auto tmp = sol.reachingPoints(1, 1, 1, 1);
//    auto tmp = sol.reachingPoints(35, 13, 455955547, 420098884);
    cout << tmp << endl;
    //
    int a =10;
    int &r = a;
    int b = 25;
    r = b;
    r++;
    cout << r << endl << a << endl << b << endl;
    cout << func(5) << endl;
    int sum = 0;
    foo(2048, sum);
    cout << sum << endl;

    return 0;
}
