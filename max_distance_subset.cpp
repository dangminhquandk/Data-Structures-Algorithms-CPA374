#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;
int T;
int N, C;
vector<int> a;

void input() {
    cin >> T;
}

// Kiểm tra xem có thể chọn C phần tử sao cho khoảng cách giữa 2 phần tử bất kỳ >= mid hay không
// Bất biến (Loop Invariant): last_pos luôn là tọa độ của phần tử được chọn gần nhất
bool check(int mid, int C) {
    int count = 1;
    int last_pos = a[0];
    for (int i = 1; i < N; i++) {
        if (a[i] - last_pos >= mid) {
            count++;
            last_pos = a[i];
            if (count >= C) return true;
        }
    }
    return count >= C;
}

void solve() {
    while (T--) {
        cin >> N >> C;
        a.resize(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        if (C > N) {
            cout << 0 << '\n';
            continue;
        }
        sort(a.begin(), a.end());
        int low = INF;
        int high = a[N - 1] - a[0];
        for (int i = 1; i < N; i++) {
            low = min(low, a[i] - a[i - 1]);
        }

        int result = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(mid, C)) {
                result = mid;
                low = mid + 1; // Thử tìm khoảng cách lớn hơn
            } else {
                high = mid - 1;
            }
        }
        cout << result << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if(fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    solve();
    return 0;
}