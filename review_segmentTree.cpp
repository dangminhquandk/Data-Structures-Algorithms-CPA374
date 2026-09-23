#include <iostream>
using namespace std;

const int INF = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
    }

    void build(vector<int>& a, int node, int L, int R) {
        if (L == R) {
            tree[node] = a[L];
            return;
        }

        int mid = (L + R) / 2;
        build(a, 2 * node, L, mid);
        build(a, 2 * node, mid + 1, R);

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        return;
    }

    int query(int node, int L, int R, int l_query, int r_query) {
        if (R < l_query || r_query < L) return INF;
        if (l_query <= L && R <= r_query) return tree[node];

        int mid = (L + R) / 2;
        int left_min = query(2 * node, L, mid, l_query, r_query);
        int right_min = query(2 * node + 1, mid + 1, R, l_query, r_query);
        
        return min(left_min, right_min);
    }

    void update(vector<int>& a, int node, int L, int R, int index) {
        if (L == R) {
            tree[node] = a[L];
            return;
        }

        int mid = (L + R) / 2;
        if (mid >= index) update(a, 2 * node, L, mid, index);
        else update(a, 2 * node + 1, mid + 1, R, index);

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        return;
    }
};