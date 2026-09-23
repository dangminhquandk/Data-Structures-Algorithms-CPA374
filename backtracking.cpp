#include <iostream>
#include <vector>
using namespace std;

const int NMAX = 30;
const int INF = 1e9 + 7;
int X[NMAX], xOpt[NMAX];
int d[NMAX][NMAX];
int K, n, load;
int f = 0;
bool visited[NMAX];
int Cmin = INF;
int f_star = INF;

void input() {
    cin >> n >> K;
    for (int i = 0; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++) {
            cin >> d[i][j];
            if (i != j) Cmin = min(Cmin, d[i][j]);
        }
}

bool check(int v) {
    if (visited[v] == true) return false;
    if (v > n) { // điểm trả khách
        if (visited[v - n] == false) return false;
    } else { // điểm đón khách
        if (load == K) return false;
    }
    return true;
}

void updateBest() {
    if (f + d[X[2*n]][0] < f_star) {
        f_star = f + d[X[2*n]][0];
        for (int i = 0; i <= 2*n; i++) xOpt[i] = X[i];
    }
}

void TRY(int k) {
    for (int v = 1; v <= 2*n; v++) {
        if (check(v)) {
            X[k] = v;
            f = f + d[X[k-1]][v];
            visited[v] = true;
            if (v <= n) load++;
            else load--;

            if (k == 2*n) updateBest();
            else {
                if (f + Cmin * (2*n - k + 1) < f_star) TRY(k + 1);
            }

             // Khôi phục trạng thái
            if (v <= n) load--; else load++;
            f = f - d[X[k - 1]][v];
            visited[v] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    X[0] = 0;
    visited[0] = true;
    TRY(1);
    cout << f_star << endl;
    return 0;
}