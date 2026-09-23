#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9 + 7; // để khởi tạo kỉ lục cho f_star
const int MAXN = 15; // Số lượng khách tối đa cần giao hàng

int n, K, Q;
int d[MAXN]; // lượng hàng khách cần giao
int c[MAXN][MAXN];// chi phí để đi giữa các điểm
vector <bool> visited(MAXN, false); // đánh dấu những hành khách đã được giao

int f; // quãng đường hiện tại đang đi
int f_star = INF; // lưu lại PA tối ưu
int Cmin = INF; // lưu đoạn đường ngắn nhất trong tất cả

void input() {
    cin >> n >> K >> Q;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++) {
            cin >> c[i][j];
            if (i != j) Cmin = min(Cmin, c[i][j]);
        }
}

// Kiểm tra xem khách v đã được giao hay còn hàng để giao hay ko
bool check(int v, int current_load) {
    if (visited[v]) return false;
    if (current_load + d[v] > Q) return false;
    return true;
}

void updateSol(int u) {
    int current_total = f + c[u][0];
        if (current_total < f_star) {
            f_star = current_total; // Update
        }
}

void Try(int k, int u, int count, int load) {
    // Điều kiện dừng: đã giao cho đủ khách
    if (count == n) {
        updateSol(u);
        return;
    }

    // Nhánh - cận (cắt nhánh nếu ko tối ưu hơn)
    if (f + Cmin * (n - count + 1) >= f_star) return;

    // Option 1: Cho xe k đi giao tiếp cho khách V
    for (int v = 1; v <= n; v++) {
        if (check(v, load)) {
            // nếu điều kiện ok thì thăm luôn và nhả hàng cho người này
            visited[v] = true;
            f += c[u][v];  // Với u là vị trí hiện tại của xe

            Try(k, v, count + 1, load + d[v]);

            // Recover - quay lui
            visited[v] = false;
            f -= c[u][v];
        }
    }

    // Option 2: Xe k đi về kho ko giao nữa, gọi xe khác (k + 1) ra
    // Điều kiện: chưa dùng hết k xe và xe k đã giao ít nhất một khách (tức u != 0)
    if (k < K && u != 0) {
        f += c[u][0]; // Cho xe k về nghỉ

        // Gọi xe k + 1 ra
        Try(k + 1, 0, count, 0);

        // Quay lui
        f -= c[u][0];
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
    Try(1, 0, 0, 0);
    cout << f_star << endl;
    return 0;
}