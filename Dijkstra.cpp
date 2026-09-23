#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;
typedef pair<int, int> pii;

const int INF = 1e9 + 7;
const int NMAX = 100005;
vector<pii> adj[NMAX];
int dist[NMAX];
int trace[NMAX];

void Dijkstra(int s,  int t) {
    for (int i = 0; i < NMAX; i++) {
        dist[i] = INF;
        trace[i] = -1;
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        pii front = pq.top();
        pq.pop();
        int d = front.first;
        int u = front.second;

        if (d > dist[u]) continue;
        if (u == t) break;

        for (pii edge : adj[u]) {
            int w = edge.first;
            int v = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                trace[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    Dijkstra(s, t);
    if (dist[t] != INF) {
        cout << dist[t] << '\n';

        vector<int> path;
        int current = t;
        while (current != - 1) {
            path.push_back(current);
            current = trace[current];
        }

        reverse(path.begin(), path.end());
        for (int x : path) cout << x << ' ';
        cout << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    return 0;
}