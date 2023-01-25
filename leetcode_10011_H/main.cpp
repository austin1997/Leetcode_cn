#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class BookMyShow {
public:
    BookMyShow(int n, int m) : n(n), m(m) {
        rowUsage.emplace_back(0);
        remains = m * n;
    }

    vector<int> gather(int k, int maxRow) {
        if (k > m || startRow > maxRow || k > remains) {
            return {};
        }
        vector<int> result;
        for (int row = startRow; row <= maxRow && row - startRow < rowUsage.size(); row++) {
            int remain = m - rowUsage[row - startRow];
            if (remain >= k) {
                result.emplace_back(row);
                result.emplace_back(rowUsage[row - startRow]);
                rowUsage[row - startRow] += k;
                break;
            }
        }

        int nextRow = startRow + rowUsage.size();
        if (result.empty() && nextRow <= maxRow) {
            result.emplace_back(nextRow);
            result.emplace_back(0);
            rowUsage.emplace_back(k);
        }

        if (!result.empty()) {
            remains -= k;
        }
        return result;
    }

    bool scatter(int k, int maxRow) {
        if (remains < k) {
            return false;
        }
        int old_k = k;
        int nextRow = startRow;
        int col = 0;
        for (; nextRow < n && k > 0 && nextRow - startRow < rowUsage.size(); nextRow++) {
            if (nextRow > maxRow) {
                return false;
            }
            int remain = m - rowUsage[nextRow - startRow];
            if (k >= remain) {
                k -= remain;
            } else {
                col = k;
                k = 0;
                break;
            }
        }
        nextRow += k / m;
        col += k % m;

        if (nextRow <= maxRow || nextRow == maxRow + 1 && col == 0) {
            for (; startRow < nextRow && !rowUsage.empty(); startRow++) {
                rowUsage.pop_front();
            }

            if (startRow < nextRow) {
                startRow = nextRow;
                rowUsage.emplace_back(col);
            } else {
                rowUsage[nextRow - startRow] = col;
            }

            remains -= old_k;
            return true;
        }

        return false;
    }

    int m = 0;
    int n = 0;
    int remains = 0;
    int startRow = 0;
    deque<int> rowUsage;
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */

int main(int argc, char const *argv[])
{
    BookMyShow obj(2, 6);
//    obj.gather(10, 1);
    obj.scatter(2, 1);
    obj.scatter(8, 0);
//    obj.gather(9, 1);
//    obj.gather(10, 2);
//    obj.gather(2, 0);
    return 0;
}
