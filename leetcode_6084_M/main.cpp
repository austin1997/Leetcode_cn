#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int helper(string& str) {
        int result = 1;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ') {
                result++;
            }
        }
        return result;
    }

    class Node {
    public:
        Node(int cnt, string name) : cnt(cnt), name(name) {

        }
        int cnt;
        string name;
    };

    string largestWordCount(vector<string>& messages, vector<string>& senders) {
        unordered_map<string, int> map;
        for (int i = 0; i < messages.size(); i++) {
            int length = helper(messages[i]);
            map.emplace(senders[i], 0).first->second+=length;
        }
        vector<Node> nodes;
        for (auto& entry : map) {
            nodes.emplace_back(entry.second, entry.first);
        }
        sort(nodes.begin(), nodes.end(), [](const Node& lhs, const Node& rhs) {
            if (lhs.cnt == rhs.cnt) {
                return lhs.name < rhs.name;
            }
            return lhs.cnt < rhs.cnt;
        });
        return nodes.back().name;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    // ["tP x M VC h lmD","D X XF w V","sh m Pgl","pN pa","C SL m G Pn v","K z UL B W ee","Yf yo n V U Za f np","j J sk f qr e v t","L Q cJ c J Z jp E","Be a aO","nI c Gb k Y C QS N","Yi Bts","gp No g s VR","py A S sNf","ZS H Bi De dj dsh","ep MA KI Q Ou"]
    //["OXlq","IFGaW","XQPeWJRszU","Gb","HArIr","Gb","FnZd","FnZd","HArIr","OXlq","IFGaW","XQPeWJRszU","EMoUs","Gb","EMoUs","EMoUs"]
    vector<string> messages = {"tP x M VC h lmD","D X XF w V","sh m Pgl","pN pa","C SL m G Pn v","K z UL B W ee","Yf yo n V U Za f np","j J sk f qr e v t","L Q cJ c J Z jp E","Be a aO","nI c Gb k Y C QS N","Yi Bts","gp No g s VR","py A S sNf","ZS H Bi De dj dsh","ep MA KI Q Ou"};
    vector<string> senders = {"OXlq","IFGaW","XQPeWJRszU","Gb","HArIr","Gb","FnZd","FnZd","HArIr","OXlq","IFGaW","XQPeWJRszU","EMoUs","Gb","EMoUs","EMoUs"};
    auto tmp = sol.largestWordCount(messages, senders);
    cout << tmp << endl;
    return 0;
}
