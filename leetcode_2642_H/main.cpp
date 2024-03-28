#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

/*
 * @lc app=leetcode.cn id=2642 lang=cpp
 *
 * [2642] 设计可以求最短路径的图类
 */

// @lc code=start
class Graph {
public:
    using NodeQueue = priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>;
    Graph(int n, vector<vector<int>>& edges) {
        dis.resize(n, vector<int>(n, numeric_limits<int>::max()));
        vector<NodeQueue> queues(n);
        for (const auto &edge : edges) {
            dis[edge[0]][edge[1]] = edge[2];
            queues[edge[0]].emplace(make_pair(edge[2], edge[1]));
        }
        for (int i = 0; i < n; i++) {
            dis[i][i] = 0;
            reconsiderRoute(i, queues[i]);
        }
        newRoutes.resize(n);
    }

    void reconsiderRoute(int from, NodeQueue& queue) {
        int n = dis.size();
        unordered_set<int> visited;
        visited.emplace(from);
        while (!queue.empty()) {
            auto curr = queue.top();
            auto mid = curr.second;
            queue.pop();
            if (!visited.emplace(mid).second) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (dis[mid][j] < numeric_limits<int>::max()) {
                    auto tmp = dis[from][mid] + dis[mid][j];
                    if (tmp < dis[from][j]) {
                        dis[from][j] = tmp;
                        queue.emplace(make_pair(tmp, j));
                    }
                }
            }
        }
    }
    
    void addEdge(vector<int> edge) {
        int n = dis.size();
        auto from = edge[0];
        auto to = edge[1];
        auto cost = edge[2];
        if (dis[from][to] <= cost) {
            return;
        }
        dis[from][to] = cost;
        NodeQueue queue;
        queue.emplace(cost, to);
        reconsiderRoute(from, queue);
        for (int i = 0; i < n; i++) {
            if (i == from || i == to) {
                continue;
            }
            if (dis[i][from] < numeric_limits<int>::max()) {
                newRoutes[i].emplace(from);
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        NodeQueue queue;
        for (auto route : newRoutes[node1]) {
            queue.emplace(make_pair(dis[node1][route], route));
        }
        reconsiderRoute(node1, queue);
        if (dis[node1][node2] < numeric_limits<int>::max()) {
            return dis[node1][node2];
        }
        return -1;
    }

    vector<vector<int>> dis;
    vector<unordered_set<int>> newRoutes;
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
// @lc code=end

int main(int argc, char const *argv[])
{
    vector<vector<int>> q = {{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}};
    Graph graph(4, q);
    std::cout << graph.shortestPath(3, 2) << std::endl;
    std::cout << graph.shortestPath(0, 3) << std::endl;
    vector<int> tmp = {1, 3, 4};
    graph.addEdge(tmp);
    std::cout << graph.shortestPath(3, 2) << std::endl;
    return 0;
}
