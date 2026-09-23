#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, 1, -1, 0};

int n, m, r, c;
int a[1000][1000];
bool flag = false;

void input() {
    cin >> n >> m >> r >> c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
}

void solve() {
    queue<pair<int, int>> q;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    
    dp[r][c] = 0;
    q.push({r, c});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == 1 || x == n || y == m || y == 1) {
            flag = true;
            cout << dp[x][y] + 1 << endl;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx <= n && 0 <= ny && ny <= m && a[nx][ny] != 1 && dp[nx][ny] == -1) {
                dp[nx][ny] = dp[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    if (flag == false) cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    solve();
    return 0;
}