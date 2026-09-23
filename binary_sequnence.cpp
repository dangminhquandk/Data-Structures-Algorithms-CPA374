#include <iostream>
using namespace std;

int n;
int x[20];

void print_result() {
    for (int i = 1; i <= n; i++) cout << x[i];
    cout << "\n";
}

void backtracking(int key) {
    for (int i = 0; i <= 1; i++) {
        x[key] = i;

        if (key == n) print_result();
        else backtracking(key + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    backtracking(1);
    return 0;
}