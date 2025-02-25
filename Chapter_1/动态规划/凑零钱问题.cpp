#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 给你k种面值的硬币，面值分别为c1, c2 ... ck，每种硬币的数量无限，再给一个总金额amount，问你最少需要几枚硬币凑出这个金额，如果不可能凑出，算法返回-1

class Solution {
    public:
        // 迭代解法
        int coinChange_1(vector<int>& coins, int amount) {
            vector<int> dp(amount + 1, amount + 1);
            // base case
            dp[0] = 0;
            if (amount == 0) return 0;
            for (int i = 1; i <= amount; ++i) {
                for (auto j : coins) {
                    if (i - j < 0) continue;
                    dp[i] = min(dp[i], dp[i - j] + 1);
                }
            }
            return (dp[amount] == amount + 1) ? -1 : dp[amount];
        }
        
        // 递归解法
        int helper(vector<int>& coins, int amount, vector<int>& memo) {

            // base case
            if (amount == 0) return 0; // 规定，若匹配到则返回0，不再进行递归
            if (amount < 0) return -1; // 规定，若未匹配到则返回-1，不再进行递归
    
            if (memo[amount] != -2)  // 注意这两行代码不能放在helper的最上面，这样会导致amount为负时越界
                return memo[amount];
    
            int res = INT_MAX;  // 初始值设为最大，寻找最小值
            // 遍历所有面额
            for (auto coin : coins) {
                int subproblem = helper(coins, amount - coin, memo);
                if (subproblem == -1) continue;  // 如果子问题无解，则跳过，选择下一个面额的硬币
                res = min(res, subproblem + 1);  // 若子问题有解，则更新最小值,这里不能拿memop[amount]和subproblem比较，因为amount在递归中是不断变化的，所以要用res
            }
            memo[amount] = (res == INT_MAX) ? -1 : res;  // 更新备忘录
            return memo[amount];
        }
    
        int coinChange_2(vector<int>& coins, int amount) {
            // 创建备忘录减少重复计算
            vector<int> memo(amount + 1, -2);  // 初始化为-2，区别于返回错误-1
            memo[0] = 0;
            int res = helper(coins, amount, memo);
            return res;
        }
    };

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    Solution s;
    cout << s.coinChange_1(coins, amount) << endl;
    cout << s.coinChange_2(coins, amount) << endl;
    return 0;
}