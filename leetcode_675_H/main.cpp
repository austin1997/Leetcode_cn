#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

class Solution {
public:
    bool canVisit(const vector<vector<int>>& forest, const vector<bool>& visited, int x, int y) {
        if (x < 0 || y < 0 || x >= m || y >= n) {
            return false;
        }
        if (forest[x][y] == 0 || visited[x * n + y]) {
            return false;
        }
        return true;
    }

    int findPath(const vector<vector<int>>& forest, const std::pair<int, int> &start, const std::pair<int, int> &end) {
        if (start == end) {
            return 0;
        }
        int result = 0;
        bool found = false;
        std::vector<bool> visited(m * n, false);
        std::deque<std::pair<int, int>> queue;
        queue.emplace_back(start);
        while(!queue.empty()) {
            std::deque<std::pair<int, int>> next;
            for (auto& current : queue) {
                if (current == end) {
                    found = true;
                    break;
                }
                visited[current.first * n + current.second] = true;
                if (canVisit(forest, visited, current.first - 1, current.second)) {
                    next.emplace_back(current.first - 1, current.second);
                }
                if (canVisit(forest, visited, current.first + 1, current.second)) {
                    next.emplace_back(current.first + 1, current.second);
                }
                if (canVisit(forest, visited, current.first, current.second - 1)) {
                    next.emplace_back(current.first, current.second - 1);
                }
                if (canVisit(forest, visited, current.first, current.second + 1)) {
                    next.emplace_back(current.first, current.second + 1);
                }
            }
            if (found) {
                break;
            }
            result++;
            queue.swap(next);
        }
        if (!found) {
            return -1;
        }
        return result;
    }

    int cutOffTree(vector<vector<int>>& forest) {
        m = forest.size();
        n = forest[0].size();
        std::vector<std::pair<int, int>> trees;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.emplace_back(i, j);
                }
            }
        }
        sort(trees.begin(), trees.end(), [&](const pair<int, int> & a, const pair<int, int> & b) {
            return forest[a.first][a.second] < forest[b.first][b.second];
        });
        int result = 0;
        std::pair<int, int> current(0, 0);
        for(auto& next : trees) {
            forest[next.first][next.second] = 1;
            auto diff = findPath(forest, current, next);
            if (diff >= 0) {
                result += diff;
            } else {
                return -1;
            }
            current = next;
        }
        return result;
    }

    int m = 0;
    int n = 0;
};

int main(int argc, char const *argv[])
{
    Solution sol;
//    std::vector<std::vector<int>> q1 = {{1,2,3}, {0, 0, 4}, {7, 6, 5}};
//    auto tmp = sol.cutOffTree(q1);
//    cout << tmp << endl;
    std::vector<std::vector<int>> q2 = {{54581641,64080174,24346381,69107959},
                                        {86374198,61363882,68783324,79706116},
                                        {668150,92178815,89819108,94701471},
                                        {83920491,22724204,46281641,47531096},
                                        {89078499,18904913,25462145,60813308}};
    auto tmp = sol.cutOffTree(q2);
    cout << tmp << endl;
    return 0;
}
