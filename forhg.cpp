#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>
using namespace std;

// n: số hành khách
// 2 * n: trạm
// K: chỗ ngồi trên xe
// c[i][j]: chi phí từ i đến j

int n, K;
int c[30][30];
int minCost = 1e9 + 7;
bool visited[30];
int Cmin = 1e9 + 7;

void input() {
    cin >> n >> K;
    for (int i = 0; i <= 2 * n; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            cin >> c[i][j];
            if (i != j) Cmin = min(Cmin, c[i][j]);
        }
    }
}

bool check(int v, int current_load) {
    if (visited[v] == true) return false;
    if (v <= n && current_load + 1 > K) return false;
    if (v > n && visited[v - n] == false) return false;
    return true;
}

void Try(int k, int u, int current_load, int current_cost) {
    // Điều kiện dừng
    if (k == 2 * n + 1) {
        minCost = min(minCost, current_cost + c[u][0]);
        return;
    }

    if (current_cost + (2 * n - k + 1) * Cmin > minCost) return;

    for (int v = 1; v <= 2 * n; v++) {
        if (check(v, current_load)) {
            visited[v] = true;

            if (v <= n) Try(k + 1, v, current_load + 1, current_cost + c[u][v]);
            else Try(k + 1, v, current_load - 1, current_cost + c[u][v]);
            visited[v] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    Try(1, 0, 0, 0);
    cout << minCost << endl;
    return 0;
}



