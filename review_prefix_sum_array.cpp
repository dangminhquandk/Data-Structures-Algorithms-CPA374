#include <iostream>
#include <vector>
using namespace std;

const long long neg_INF = -(1e9 + 7);
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n; cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];
    long long max_even = neg_INF;
    for (int i = 1; i < n + 1; i++) {
        if (a[i] % 2 == 0) max_even = max(max_even, a[i]);
    }
    if (n % 2 != 0 && max_even == neg_INF) {
        cout << "NOT FOUND" << endl;
        return 0;
    }

    vector<long long > S(n + 1, 0);
    for (int i = 1; i < n + 1; i++) S[i] = S[i - 1] +  a[i];

    long long max_even_sequence_with_even, min_even_sequence, max_even_sequence_with_odd, min_odd_sequence;
    int i = 0;
    int j = 0;
    while (S[i] % 2 != 0) i++;
    min_even_sequence = max_even_sequence_with_even = S[i];
    while (i <= n && S[j] % 2 == 0) j++;
    min_odd_sequence = max_even_sequence_with_odd = S[j];

    for (int i = 1; i < n + 1; i++) {
        if (S[i] % 2 == 0) {
            max_even_sequence_with_even = max(S[i] - min_even_sequence, max_even_sequence_with_even);
            min_even_sequence = min(min_even_sequence, S[i]);
        } else {
            max_even_sequence_with_odd = max(S[i] - min_odd_sequence, max_even_sequence_with_odd);
            min_odd_sequence = min(min_odd_sequence, S[i]);
        }
    }
    long long result = max(max_even_sequence_with_even, max_even_sequence_with_odd);
    result = max(result, max_even);
    cout << result << endl;
    return 0;
}