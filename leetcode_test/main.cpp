#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<unordered_set<int>> graphs;
        vector<int> graphWeight;
        vector<int> graphIndex(n, -1);
        for (auto& edge : edges) {
            auto u = edge[0];
            auto v = edge[1];
            auto w = edge[2];
            if (graphIndex[u] < 0 && graphIndex[v] < 0) {
                auto index = graphs.size();
                graphs.emplace_back();
                graphs.back().emplace(u);
                graphs.back().emplace(v);
                graphIndex[u] = index;
                graphIndex[v] = index;
                graphWeight.emplace_back(w);
            } else if (graphIndex[u] < 0) {
                auto index = graphIndex[v];
                auto& graph = graphs[index];
                graph.emplace(u);
                graphIndex[u] = index;
                graphWeight[index] &= w;
            } else if (graphIndex[v] < 0) {
                auto index = graphIndex[u];
                auto& graph = graphs[index];
                graph.emplace(v);
                graphIndex[v] = index;
                graphWeight[index] &= w;
            } else {
                auto indexU = graphIndex[u];
                auto indexV = graphIndex[v];
                if (indexU == indexV) {
                    graphWeight[indexU] &= w;
                    continue;
                }
                auto& graphU = graphs[indexU];
                auto& graphV = graphs[indexV];
                graphU.insert(graphV.begin(), graphV.end());
                for (auto i : graphV) {
                    graphIndex[i] = indexU;
                }
                graphV.clear();
                graphWeight[indexU] &= graphWeight[indexV];
                graphWeight[indexU] &= w;
            }
        }

        vector<int> result;
        for (auto& q : query) {
            auto s = q[0];
            auto t = q[1];
            if (s == t) {
                result.emplace_back(0);
            } else if (graphIndex[s] == graphIndex[t] &&  graphIndex[t] != -1) {
                result.emplace_back(graphWeight[graphIndex[s]]);
            } else {
                result.emplace_back(-1);
            }
        }
        return result;
        
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    // n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
    // vector<vector<int>> edges = {{0,1,7},{1,3,7},{1,2,1}};
    // vector<vector<int>> query = {{0,3},{3,4}};
    // cout << sol.minimumCost(5, edges, query).size() << endl;

    // n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
    // 8
// [[3,6,6],[6,1,0],[1,3,1]]
// [[5,7],[6,2]]
    vector<vector<int>> edges = {{3,6,6},{6,1,0},{1,3,1}};
    vector<vector<int>> query = {{5,7},{6,2}};
    cout << sol.minimumCost(8, edges, query).size() << endl;
    return 0;
}
