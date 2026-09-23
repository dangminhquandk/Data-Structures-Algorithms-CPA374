#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int d;
    int p;

    Job() : d(0), p(0) {}
    Job(int _d, int _p) : d(_d), p(_p) {}
};

int n;
vector<Job> a;
int max_deadline = 0;

void input() {
    if (!(cin >> n)) return;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int d, p; cin >> d >> p;
        a[i] = Job(d, p);
        max_deadline = max(max_deadline, d);
    }
}

void sort_Job() {
    // Sắp xếp các công việc theo lợi nhuận p giảm dần để ưu tiên công việc có giá trị cao nhất
    sort(a.begin(), a.end(), [](const Job& x, const Job& y) {
        if (x.p != y.p) return x.p > y.p;
        return x.d < y.d;
    });
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    input();
    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    sort_Job();
    vector<bool> slot_taken(max_deadline + 1, false);
    
    int result = 0;
    // Tham lam: Với mỗi công việc từ lợi nhuận cao nhất, chọn slot thời gian muộn nhất còn trống <= d
    for (int i = 0; i < n; i++) {
        for (int j = a[i].d; j >= 1; j--) {
            if (!slot_taken[j]) {
                slot_taken[j] = true;
                result += a[i].p;
                break;
            }
        }
    }
    cout << result << "\n";
    return 0;
}