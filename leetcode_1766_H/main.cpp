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
 * @lc app=leetcode.cn id=1766 lang=cpp
 *
 * [1766] 互质树
 */

// @lc code=start
class Solution {
public:
    void buildTree(vector<unordered_set<int>>& tree, const vector<vector<int>>& edges) {
        for (const auto& edge : edges) {
            tree[edge[0]].emplace(edge[1]);
            tree[edge[1]].emplace(edge[0]);
        }
    }


    void helper(vector<unordered_set<int>>& tree, vector<int>& parent, const vector<int>& nums, int curr, vector<int>& result) {
        result[curr] = parent[curr];
        while(std::gcd(nums[result[curr]], nums[curr]) != 1) {
            if (nums[curr] % nums[result[curr]] == 0) {
                result[curr] = result[result[curr]]; 
            } else {
                result[curr] = parent[result[curr]];
            }
        }
        for (auto child : tree[curr]) {
            tree[child].erase(curr);
            parent[child] = curr;
            helper(tree, parent, nums, child, result);
        }
    }

    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<int> result(n, -1);
        vector<unordered_set<int>> tree(n);
        vector<int> parent(n);
        nums.push_back(1);
        parent[0] = n;
        buildTree(tree, edges);
        helper(tree, parent, nums, 0, result);
        for (auto& num : result) {
            if (num >= n) {
                num = -1;
            }
        }
        return result;
    }
};
// @lc code=end

int main(int argc, char const *argv[])
{
    Solution sol;
    // vector<int> nums = {2,3,3,2};
    // vector<vector<int>> edges = {{0,1},{1,2},{1,3}};
    // vector<int> nums = {3,2,6,2,6};
    // vector<vector<int>> edges = {{0,2},{0,1},{2,4},{2,3}};
    // vector<int> nums = {9,16,30,23,33,35,9,47,39,46,16,38,5,49,21,44,17,1,6,37,49,15,23,46,38,9,27,3,24,1,14,17,12,23,43,38,12,4,8,17,11,18,26,22,49,14,9};
    // vector<vector<int>> edges = {{17,0},{30,17},{41,30},{10,30},{13,10},{7,13},{6,7},{45,10},{2,10},{14,2},{40,14},{28,40},{29,40},{8,29},{15,29},{26,15},{23,40},{19,23},{34,19},{18,23},{42,18},{5,42},{32,5},{16,32},{35,14},{25,35},{43,25},{3,43},{36,25},{38,36},{27,38},{24,36},{31,24},{11,31},{39,24},{12,39},{20,12},{22,12},{21,39},{1,21},{33,1},{37,1},{44,37},{9,44},{46,2},{4,46}};
    vector<int> nums;
    vector<vector<int>> edges;
    int n = 100000;
    for (int i = 0; i < n; i += 2) {
        std::vector<int> tmp = {i, i + 2};
        edges.push_back(tmp);
        tmp = {i, i + 1};
        edges.push_back(tmp);
    }
    nums.push_back(3);
    for (int i = 1; i < n; i++) {
        if (i % 2 == 1) {
            nums.push_back(2);
        } else {
            nums.push_back(6);
        }
    }
    std::cout << sol.getCoprimes(nums, edges).size() << std::endl;
    return 0;
}
