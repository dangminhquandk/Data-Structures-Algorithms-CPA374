#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n;
vector<int> a;
int count_odd = 0;
int maxlength = 0;

void input() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x % 2 == 0) {
            a[i] = 0;
            maxlength = 1;
        }
        else {
            a[i] = 1;
            count_odd++;
        }
    }
}

void process() {
    if (count_odd % 2 == 0) {
        maxlength = n;
        return;
    }
    int left = 0, right = n - 1;
    while (left < n) {
        if (a[left] == 1) {
            maxlength = max(left, n - left - 1);
            break;
        }
        left++;
    }
    while (right >= 0) {
        if (a[right] == 1) {
            int temp = max(right, n - right - 1);
            maxlength = max(temp, maxlength);
            break;
        }
        right--;
    }
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    process();
    cout << maxlength << endl;
    return 0;
}