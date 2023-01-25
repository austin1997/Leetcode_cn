#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Time {
public:
    Time(int a, int b) : end_time(a), server(b) {

    }
    int end_time = 0;
    int server = -1;
    bool operator<(const Time& rhs) const {
        return this->end_time < rhs.end_time;
    }
};

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> job_cnt(k, 0);
        vector<int> end_time(k, 0);
        multiset<Time> end_time_set;
        for (int i = 0; i < k; i++) {
            end_time_set.emplace(0, i);
        }
        int length = arrival.size();
        int max = 0;
        int min_end_time = 0;
        Time finder(0, -1);
        for (int i = 0; i < length; i++) {
            int server = findServer(k, end_time, i, arrival[i], end_time_set);
#ifndef NDEBUG
            int server_debug = findServer(k, end_time, i, arrival[i]);
            if (server != server_debug) {
                server = findServer(k, end_time, i, arrival[i], end_time_set);
            }
#endif
            if (server < 0) {
                continue;
            }
            finder.end_time = end_time[server];
            auto range = end_time_set.equal_range(finder);
            for (; range.first != range.second; range.first++) {
                if (range.first->server == server) {
                    end_time_set.erase(range.first);
                    break;
                }
            }
            end_time[server] = arrival[i] + load[i];
            end_time_set.emplace(end_time[server], server);
            job_cnt[server]++;
            max = std::max(max, job_cnt[server]);
        }
        vector<int> result;
        for (int i = 0; i < k; i++) {
            if (job_cnt[i] >= max) {
                result.emplace_back(i);
            }
        }
        return result;
    }

    int findServer(int k, const vector<int>& end_time, int i, int start_time, multiset<Time>& end_time_set) {
        int base = i % k;
        if (end_time[base] <= start_time) {
            return base;
        }
        auto iter = end_time_set.begin();
        int result = -1;
        for (; iter != end_time_set.end() && (*iter).end_time <= start_time; iter++) {
            int tmp = (*iter).server;
            if (tmp < base) {
                tmp += k;
            }
            if (result < 0) {
                result = tmp;
            } else {
                result = std::min(result, tmp);
            }
        }
        return result % k;
    }

    int findServer(int k, const vector<int>& end_time, int i, int start_time) {
        for (int j = i; j < i + k; j++) {
            if (end_time[j % k] <= start_time) {
                return j % k;
            }
        }
        return -1;
    }

};

int main(int argc, char const *argv[])
{
    Solution sol;
//    cout << sol.maxConsecutiveAnswers("TTFF", 2) << endl;
//    vector<int> arrival = {1,2,3,4,5};
//    vector<int> load = {5,2,3,3,3};
//22
//[2,4,6,10,11,13,14,15,16,18,20,21,26,27,31,32,33,35,36,37,40,46,47,48,49,56,59,62,63,66,71,74,75,76,77,78,79,81,84,86,87,88,91,92,93,94,95,96,98]
//[6,43,69,74,23,70,68,39,15,17,72,71,8,71,53,75,9,48,96,42,43,4,81,92,14,20,7,61,60,8,18,4,13,14,20,77,81,96,52,38,91,71,65,13,77,19,82,30,54]
    vector<int> arrival = {2,4,6,10,11,13,14,15,16,18,20,21,26,27,31,32,33,35,36,37,40,46,47,48,49,56,59,62,63,66,71,74,75,76,77,78,79,81,84,86,87,88,91,92,93,94,95,96,98};
    vector<int> load = {6,43,69,74,23,70,68,39,15,17,72,71,8,71,53,75,9,48,96,42,43,4,81,92,14,20,7,61,60,8,18,4,13,14,20,77,81,96,52,38,91,71,65,13,77,19,82,30,54};
    auto tmp = sol.busiestServers(22, arrival, load);
    cout << tmp.size() << endl;
    return 0;
}
