
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<string> generateBoard(vector<vector<int>> &map, int n) {
            vector<string> board(n, "");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; ++j) {
                    if (map[i][j] == 0)
                        board[i] += ".";
                    else
                        board[i] += "Q";
                }
            }
            return board;
        }
    
        bool isValid(vector<vector<int>>& map, int row, int column) {
            int n = map.size();
            // 如果列被占用
            for (int i = 0; i < row; ++i) {
                if (map[i][column] == 1) {
                    return false;
                }
            }
            // 检查左上对角线
            for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; --i, --j) {
                if (map[i][j] == 1) {
                    return false;
                }
            }
            // 检查右上对角线
            for (int i = row - 1, j = column + 1; i >= 0 && j < n; --i, ++j) {
                if (map[i][j] == 1) {
                    return false;
                }
            }
            return true;
        }
    
        void backTrace(vector<vector<string>>& res, vector<vector<int>>& map, int row) {
            int n = map.size();
            // 如果已经递归结束，则保存结果
            if (row == n) {
                auto board = generateBoard(map, n);
                res.push_back(board);
                return;
            }
            // 遍历可选哪些列
            for (int column = 0; column < n; ++column) {
                // 检查该位置是否有效
                if (!isValid(map, row, column)) {
                    continue;
                }
                // 将皇后摆放在该位置
                map[row][column] = 1;
                backTrace(res, map, row + 1);
                // 对于每一行的皇后，一定会得到一个解，得到这个解后，开始探寻下一个解，先把皇后挪走
                map[row][column] = 0;
            }
            // 如果这一行所有位置都遍历了，就返回
        }
    
        vector<vector<string>> solveNQueens(int n) {
            // 保存棋谱
            vector<vector<string>> res;
            // 初始化棋盘，0为空，1为皇后
            vector<vector<int>> map(n, vector<int>(n, 0));
            backTrace(res, map, 0);  // 从第0行开始递归
            return res;
        }
    };

int main() {
    int n;
    cin >> n;
    Solution s;
    vector<vector<string>> res = s.solveNQueens(n);
    for (auto board : res) {
        for (auto row : board) {
            cout << row << endl;
        }
        cout << endl;
    }
    return 0;
}