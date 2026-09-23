#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;
int n, K, Q;
vector<int> d;
int c[15][15];
bool visited[15];
int f_star = INF;
int Cmin = INF;
int start_v[15];

void input() {
    cin >> n >> K >> Q;
    d.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; ++j) {
            cin >> c[i][j];
            if (i != j) Cmin = min(Cmin, c[i][j]);
        }
    }
}

bool check(int v, int current_load) {
    if (visited[v]) return false;
    if (current_load + d[v] > Q) return false;
    return true;
}

void Try(int k, int u, int count, int current_load, int current_cost) {
    if (count == n) {
        if (k == K) f_star = min(f_star, current_cost + c[u][0]);
        return;
    }

    if (current_cost + Cmin * (n - count + 1) >= f_star) return;

    for (int v = 1; v <= n; ++v) {
        if (check(v, current_load)) {

            if (u == 0 && v < start_v[u]) continue;
            visited[v] = true;

            int old_start = start_v[k];
            if (u == 0) start_v[k] = v;
            Try(k, v, count + 1, current_load + d[v], current_cost + c[u][v]);
            
            if (u == 0) start_v[k] = old_start;
            visited[v] = false;
        }
    }
    if (k < K && u != 0) {
        Try (k + 1, 0, count, 0, current_cost + c[u][0]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    Try(1, 0, 0, 0, 0);
    cout << f_star << endl;
    return 0;
}