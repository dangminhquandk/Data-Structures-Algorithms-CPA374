#include <iostream>
using namespace std;

const int MAX_DIM = 105;
const int MAX_N = 25;

int H, W, n;
int h[MAX_N], w[MAX_N];
bool mark[MAX_DIM][MAX_DIM];
bool is_possible = false;

bool check(int vo, int vx, int vy, int k) {
    int wk = w[k], hk = h[k];
    if (vo == 1) {
        wk = h[k];
        hk = w[k];
    }
    
    if (vx + wk > W) return false;
    if (vy + hk > H) return false;
    
    for (int i = vx; i < vx + wk; i++) {
        for (int j = vy; j < vy + hk; j++) {
            if (mark[i][j]) return false;
        }
    }
    return true;
}

void update(int vo, int vx, int vy, int k, bool mark_value) {
    int wk = w[k], hk = h[k];
    if (vo == 1) {
        wk = h[k];
        hk = w[k];
    }
    
    for (int i = vx; i < vx + wk; i++) {
        for (int j = vy; j < vy + hk; j++) {
            mark[i][j] = mark_value;
        }
    }
}

void Try(int k) {
    if (is_possible) return;

    if (k > n) {
        is_possible = true;
        return;
    }

    for (int vo = 0; vo <= 1; vo++) {
        // Tránh trùng lặp trạng thái nếu mảnh cắt hình vuông
        if (vo == 1 && w[k] == h[k]) continue;

        int wk = w[k], hk = h[k];
        if (vo == 1) {
            wk = h[k];
            hk = w[k];
        }

        for (int vx = 0; vx <= W - wk; vx++) {
            for (int vy = 0; vy <= H - hk; vy++) {
                
                if (check(vo, vx, vy, k)) {
                    update(vo, vx, vy, k, true);
                    
                    Try(k + 1);
                    
                    update(vo, vx, vy, k, false);
                    if (is_possible) return;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> H >> W)) return 0;
    cin >> n;
    
    int total_area_needed = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> w[i];
        total_area_needed += h[i] * w[i];
    }

    if (total_area_needed > H * W) {
        cout << 0 << "\n";
        return 0;
    }

    Try(1);

    if (is_possible) {
        cout << 1 << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}
