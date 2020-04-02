#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void addLife(size_t i, size_t j, vector<vector<int>>& board) {
        if (i >= 0 && i < board.size() && j >= 0 && j < board[0].size()) {
            ++board[i][j];
        }
    }

    void gameOfLife(vector<vector<int>>& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }
        vector<vector<int>> ret(board.size(), vector<int>(board[0].size(), 0));
        for (size_t i = 0; i < board.size(); i++)
        {
            for (size_t j = 0; j < board[i].size(); j++)
            {
                if (!board[i][j]) {
                    continue;
                }
                addLife(i-1, j, ret);
                addLife(i+1, j, ret);
                addLife(i-1, j-1, ret);
                addLife(i-1, j+1, ret);
                addLife(i+1, j-1, ret);
                addLife(i+1, j+1, ret);
                addLife(i, j-1, ret);
                addLife(i, j+1, ret);
            }
        }
        for (size_t i = 0; i < board.size(); i++)
        {
            for (size_t j = 0; j < board[i].size(); j++)
            {
                if (ret[i][j] < 2) {
                    board[i][j] = 0;
                }else if (ret[i][j] > 3) {
                    board[i][j] = 0;
                }else if (ret[i][j] == 3)
                {
                    board[i][j] = 1;
                }
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<vector<int>> board1 = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    sol.gameOfLife(board1);
    return 0;
}
