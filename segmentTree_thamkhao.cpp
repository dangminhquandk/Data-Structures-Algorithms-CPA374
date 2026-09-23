#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

const int maxN =1e7;
int N, m, a[maxN], maxVal[maxN];

void build(int id, int L, int R) {
    if(L==R) {
        maxVal[id] = a[L];    return;
    }
    int mid = (L+R)/2;
    build(2*id, L, mid); build(2*id+1, mid+1, R);
    maxVal[id] = max(maxVal[2*id], maxVal[2*id+1]);
}

int getmax(int id, int L, int R, int i, int j) {
    if (i>R || j<L) return INT_MIN;
    if (i<=L && j>=R) return maxVal[id];
    int mid = (L+R)/2;
    return max(getmax(2*id,L,mid,i,j), 
            getmax(2*id+1,mid+1,R,i,j));
}

void update(int id, int L, int R, int i, int v) { //update a[i]=v
    if (L==R) { //==i
        maxVal[id] = v; return;
    } 
    int mid = (L+R)/2;
    if (i<=mid) update(2*id, L, mid, i, v);
    else update(2*id+1, mid+1, R, i, v);
    maxVal[id] = max(maxVal[2*id], maxVal[2*id+1]);
}

int main() {
    cin >> N;
    for (int i=1; i<=N; i++) cin >> a[i];
    cin >> m;
    build(1,1,N);
    while (m--) {
        string cmd; cin >> cmd;
        if (cmd == "get-max") {
            int i, j; cin >> i >> j;
            cout << getmax(1,1,N,i,j) << endl;
        }
        if (cmd == "update") {
            int i, v; cin >> i >> v;
            update(1, 1, N, i, v);
        }
    }
    return 0;
}
