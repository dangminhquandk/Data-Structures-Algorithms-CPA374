#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Job {
    int d;
    int p;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n; cin >> n;
    vector<Job> jobs(n);
    int max_deadline = 0;
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].d >> jobs[i].p;
        max_deadline = max(max_deadline, jobs[i].d);
    }

    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.d > b.d;
    });

    priority_queue<int> pq;
    long long total_profit = 0;
    int i = 0;
    for (int t = max_deadline; t >= 1; --t) {
        while (i < n && jobs[i].d == t) {
            pq.push(jobs[i].p);
            i++;
        }

        if (!pq.empty()) {
            total_profit += 1l * pq.top();
            pq.pop();
        }
    }

    cout << total_profit << endl;
    return 0;
}