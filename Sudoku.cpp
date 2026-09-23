#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

int C[10][10];
int total = 0;

void input() {
    for (int i = 1; i <= 9 ; i++) {
        for (int j = 1; j <= 9; j++) {
            cin >> C[i][j];
        }
    }
}

bool check(int r, int c, int x) {
    for (int i = 1; i <= 9; i++) {
        if (C[i][c] == x || C[r][i] == x) return false;
    }
    int r_start = r - (r - 1) % 3;
    int c_start = c  - (c - 1) % 3;
    int r_end = r_start + 3, c_end = c_start + 3;
    for (int i = r_start; i < r_end ; i++) {
        for (int j = c_start; j < c_end; j++) {
            if (C[i][j] == x) return false;
        }
    }
    return true;
}

void Try(int r, int c) {
    if (r == 10 && c == 1) {
        total++;
        return;
    }

    if (C[r][c] != 0) {
        if (c == 9) Try(r + 1, 1);
        else Try(r, c + 1);
    }
    else {
        for (int x = 1; x <= 9; x++) {
            if (check(r, c, x)) {
                C[r][c] = x;

                if (c == 9) Try(r + 1, 1);
                else Try(r, c + 1);

                C[r][c] = 0;
            }
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

    input();
    Try(1, 1);
    cout << total << endl;
    return 0;
}