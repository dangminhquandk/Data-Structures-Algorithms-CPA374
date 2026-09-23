#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
    }

    void build (const vector<int>& a, int node, int L, int R) {
        if (L == R) {
            tree[node] = a[L];
            return;
        }

        int mid = (L + R) / 2;
        build(a, 2 * node, L, mid);             // nhánh trái
        build(a, 2 * node + 1, mid + 1, R);     // nhánh phải

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int L, int R, int l_query, int r_query) {
        if (L > r_query || R < l_query) return INF; 
        if (l_query <= L && R <= r_query) return tree[node];

        int mid = (L + R) / 2;
        int min_left = query(2 * node, L, mid, l_query, r_query);
        int min_right = query(2 * node + 1, mid + 1, R, l_query, r_query);

        return min(min_left, min_right);
    }
};


int main() {
    // Optimize I/O operation
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SegmentTree st(n);
    st.build(a, 1, 0, n - 1);

}


