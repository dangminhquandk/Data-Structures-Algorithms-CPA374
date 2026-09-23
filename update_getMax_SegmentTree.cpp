#include <iostream>
#include <vector>

using namespace std;

const int _INF = - (1e9 + 7);

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree (int _n) {
        n = _n;
        tree.assign(4 * n, 0);
    }

    void build (vector<int>& a, int node, int L, int R) {
        if (L == R) {
            tree[node] = a[L];
            return;
        }

        int mid = (L + R) / 2;
        build(a, 2 * node, L, mid);
        build(a, 2 * node + 1, mid + 1, R);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int get_max (int node, int L, int R, int l_query, int r_query) {
        if (R < l_query || r_query < L) return _INF;
        if (l_query <= L && R <= r_query) return tree[node];

        int mid = (L + R) / 2;
        int left_max = get_max(2 * node, L, mid, l_query, r_query);
        int right_max = get_max(2 * node + 1, mid + 1, R, l_query, r_query);

        return max(left_max, right_max);
    }

    void update(vector<int>& a, int node, int L, int R, int index) {
        int mid = (L + R) / 2;
        if (L == R) {
            tree[node] = a[L];
            return;
        }
        if (mid >= index) update(a, 2 * node, L, mid, index);
        if (mid < index) update(a, 2 * node + 1, mid + 1, R, index);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SegmentTree st(n);
    st.build(a, 1, 0, n - 1);

    int m; cin >> m;
    int i, j;
    string cmd;

    while (m--) {
        cin >> cmd;
        cin >> i >> j;
        if (cmd == "get-max") cout << st.get_max(1, 0, n - 1, i - 1, j - 1) << "\n";
        else {
            a[i - 1] = j;
            st.update(a, 1, 0, n - 1, i - 1);
        }
    }
}