#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 斐波那契数列的前几项是：0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

// 最初的做法
int fib(int num) {
    if (num == 1 || num == 2) {
        return 1;
    }
    return fib(num - 1) + fib(num - 2);
}

// 使用备忘录来减少重复计算（剪枝）
int fib_with_memo_helper(int num, vector<int>& memo) {
    if (memo[num] != 0) {
        return memo[num];
    }
    memo[num] = fib_with_memo_helper(num - 1, memo) + fib_with_memo_helper(num - 2, memo);
    return memo[num];
}

void fib_with_memo(int num) {
    vector<int> memo(num + 1, 0);
    memo[1] = 1;
    memo[2] = 1;
    int res = fib_with_memo_helper(num, memo);
    cout << res << endl;
}

// 使用自底向上的方法，动态规划
int fib_with_dp(int num) {
    vector<int> dp(num + 1, 0);
    dp[1] = 1;
    dp[2] = 1;
    if (dp[num] != 0) {
        return dp[num];
    }
    for (int i = 3; i <= num; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[num];
}

// 优化空间复杂度的动态规划
int fib_with_dp_optimal(int num) {
    if (num == 1 || num == 2) {
        return 1;
    }
    int pre1 = 1, pre2 = 1, res;
    for (int i = 3; i <= num; ++i) {
        res = pre1 + pre2;
        pre1 = pre2;
        pre2 = res;
    }
    return res;
}

int main() {
    int num;
    while(cin >> num) {
        auto start = high_resolution_clock::now();
        cout << fib(num) << endl;
        auto end = high_resolution_clock::now();
        cout << "fib time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

        start = high_resolution_clock::now();
        fib_with_memo(num);
        end = high_resolution_clock::now();
        cout << "fib_with_memo time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

        start = high_resolution_clock::now();
        cout << fib_with_dp(num) << endl;
        end = high_resolution_clock::now();
        cout << "fib_with_dp time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

        start = high_resolution_clock::now();
        cout << fib_with_dp_optimal(num) << endl;
        end = high_resolution_clock::now();
        cout << "fib_with_dp_optimal time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
    }
}