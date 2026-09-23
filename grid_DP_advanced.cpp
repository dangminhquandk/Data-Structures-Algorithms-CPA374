#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;
const int MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int H, W;
    cin >> H >> W;
    vector<vector<int>> a(H + 1, vector<int>(W + 1, 0)), dp(H + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            char x; cin >> x;
            a[i][j] = (x == '.') ? 1 : 0;
        }
    }
    for (int i = 1; i <= H; i++) {
        if (a[i][1] == 0) break;
        dp[i][1] = 1;
    }
    for (int i = 1; i <= H; i++) {
        if (a[1][i] == 0) break;
        dp[1][i] = 1;
    }
    for (int i = 2; i <= H; i++) {
        for (int j = 2; j <= W; j++) {
            if (a[i - 1][j] == 1) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            if (a[i][j - 1] == 1) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }
    cout << dp[H][W] << endl;
    return 0;
}