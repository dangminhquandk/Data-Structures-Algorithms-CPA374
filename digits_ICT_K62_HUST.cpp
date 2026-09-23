#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int n;
// int sum[11000];
int X[7]; // I, C, T, H, U, S, K
// ICT - K62 + HUST = N
bool visited[10];
int total = 0;

bool check(int x, int k) {
    if (visited[x]) return false;
    if (x == 0 && (k == 0 || k == 6 || k == 3)) return false;
    return true;
}

void Try(int k) {
    if (k == 7) {
        int ICT = 100 * X[0] + 10 * X[1] + X[2];
        int K62 = 100 * X[6] + 62;
        int HUST = 1000 * X[3] + 100 * X[4] + 10 * X[5] + X[2];
        int res = ICT - K62 + HUST;
        // sum[res]++;
        if (res == n) total++;
        return;
    }

    for (int x = 1; x <= 9; ++x) {
        if (check(x, k)) {
            X[k] = x;
            visited[x] = true;

            Try(k + 1);

            visited[x] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    cin >> n;
    Try(0);
    // cout << sum[n] << endl;
    cout << total << endl;
    return 0;
}