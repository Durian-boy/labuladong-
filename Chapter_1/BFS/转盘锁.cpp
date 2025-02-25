#include <iostream>
#include <string>
#include <queue>
#include <set>

using namespace std;

class Solution {
    public:
        string plusOne(string str, int idx) {
            if (str[idx] == '9')
                str[idx] = '0';
            else
                str[idx]++;
            return str;
        }
    
        string minusOne(string str, int idx) {
            if (str[idx] == '0')
                str[idx] = '9';
            else
                str[idx]--;
            return str;
        }
    
        int openLock(vector<string>& deadends, string target) {
            queue<string> res;
            set<string> visited;
            set<string> dead;
            for (auto it : deadends) {
                dead.insert(it);
            }
            res.push("0000");  // 初始化
            int num_cur = 1;  // 记录当前层元素数量
            int min = 0;  // 记录最少拨动次数
            while(!res.empty()) {
                int num_next = 0;
                for (int i = 0; i < num_cur; ++i) {
                    string tmp = res.front();
                    res.pop();
                    // 如果遇到deadends，则跳过
                    if (dead.count(tmp) == 1)
                        continue;
                    // 如果匹配到target则返回min
                    if (tmp == target) {
                        return min;
                    }
                    // 如果已经判断过，则跳过，可以考虑放在下面添加元素的地方判断，以优化空间复杂度
                    if (visited.count(tmp) == 1)
                        continue;
                    // 将未判断过的组合加入visited，避免重复判断，导致无法退出循环
                    visited.insert(tmp);
                    // 若上面都没有匹配到，那就将8种情况加入队列
                    for (int j = 0; j < 4; ++j) {
                        string s1 = plusOne(tmp, j);
                        res.push(s1);
                        num_next++;
                        string s2 = minusOne(tmp, j);
                        res.push(s2);
                        num_next++;
                    }
                }
                num_cur = num_next;
                min++;
            }
            // 若不是上面返回，则说明没匹配到，返回-1
            return -1;
        }
};

int main() {
    vector<string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    string target = "0202";
    Solution s;
    cout << s.openLock(deadends, target) << endl;
    return 0;
}