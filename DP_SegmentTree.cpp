#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
    }
    
    void update(int node, int l, int r, int val, int idx) {
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = l + (r - l) / 2;
        if (mid >= idx) update(2 * node, l, mid, val, idx);
        else update(2 * node + 1, mid + 1, r, val, idx);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int l, int r, int l_q, int r_q) {
        if (r < l_q || l > r_q) return -(1e9 + 7);
        if (l_q <= l && r <= r_q) return tree[node];

        int mid = l + (r - l) / 2;
        int leftMax = query(2 * node, l, mid, l_q, r_q);
        int rightMax = query(2 * node + 1, mid + 1, r, l_q, r_q);

        return max(leftMax, rightMax);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n, l1, l2; cin >> n >> l1 >> l2;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> dp(n + 1);

    SegmentTree st(n);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (i <= l1) {
            dp[i] = a[i];
        }else {
            int start = max(1, i - l2);
            dp[i] = a[i] + st.query(1, 1, n, start, i - l1);
        }
        res = max(res, dp[i]);
        st.update(1, 1, n, dp[i], i);
    }
    cout << res << endl;
    return 0;
}