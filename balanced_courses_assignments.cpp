#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;
const int MMAX = 31;        // Số lượng tối đa khoá học
const int NMAX = 11;        // Số lượng tối đa GV

int m, n;
bool can_teach[MMAX][NMAX]; // Thày nào có thể dạy môn nào
int assignment[NMAX];       // Giao môn thứ i cho thầy nào r
int load[MMAX];             // Số lượng môn thầy thứ i đg đảm nhận
int optimalOption = INF;
bool conflicts[NMAX][NMAX]; // Xem những môn nào xung đột lẫn nhau

void input() {
    if (!(cin >> m >> n)) return;
    for (int t = 1; t <= m; t++) {
        int k; cin >> k;
        while (k--) {
            int course; cin >> course;
            can_teach[t][course] = true;
        }
    }
    int conflict_pairs; cin >> conflict_pairs;
    while (conflict_pairs--) {
        int i, j; cin >> i >> j;
        conflicts[i][j] = true;
        conflicts[j][i] = true;
    }
    
    return;
}

bool check(int t, int c) {
    // Kiểm tra xem trong các môn đã giao cho t, có môn nào bị xung đột vs c ko
    for (int i = 1; i < c; i++) {
        if (assignment[i] == t && conflicts[i][c]) return false;
    }
    return true;
}

void backtrack(int c) {
    // Ktra xem đã giao hết n môn
    if (c > n) {
        int maxVal = 0;
        for (int i = 1; i <= m; i++) {
            maxVal = max(maxVal, load[i]);
        }

        optimalOption = min(optimalOption, maxVal);
        return;
    }

    // Giao môn c cho thầy t
    for (int t = 1; t <= m; t++) {
        if (can_teach[t][c] && check(t, c)) {
            load[t]++;

            if (load[t] < optimalOption) {
                assignment[c] = t; // Giao môn c cho thầy t
                backtrack(c + 1);
            }
            
            // Nếu ko thì lấy lại môn c ko giao cho thầy t nữa
            load[t]--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }


    input();
    backtrack(1);
    if (optimalOption == INF) cout << -1 << endl;
    else cout << optimalOption << endl;
    return 0;
}