# 🕸️ Graph Theory & Algorithms Master Handbook

> **Target**: Competitive Programming & HUST Algorithm Curriculum.  
> **Standard**: C++20 | Cache-Friendly | Zero-Memory-Leak | Strict Big-O Complexity.

---
## 1. 📐 Mô Hình Hóa Toán Học & Cấu Trúc Đồ Thị

Mọi bài toán thực tế (bản đồ, mạng lưới, lưới ô vuông $R \times C$, đồ thị phụ thuộc công việc) đều được quy đổi về mô hình toán học trừu tượng:

$$G = (V, E)$$

* **Tập đỉnh (Vertices) $V$**: Đại diện cho các thực thể / trạng thái. Trong các bài toán nâng cao, một đỉnh không chỉ là một chỉ số $u \in \{1 \dots N\}$ mà là một **vector trạng thái** $(r, c, \text{mask}, \text{fuel})$.
* **Tập cạnh (Edges) $E$**: Quan hệ kết nối hoặc bước chuyển trạng thái có hướng hoặc vô hướng, có trọng số $w(e)$ hoặc không có trọng số.

### Biểu Diễn Đồ Thị: Tối Ưu Hóa Bộ Nhớ Đệm (Cache-Friendly Architecture)

| Cấu trúc | Độ phức tạp bộ nhớ | Duyệt đỉnh kề $u$ | Kiểm tra tồn tại cạnh $(u, v)$ | Ưu/Nhược điểm & Kịch bản thực tế |
| :--- | :---: | :---: | :---: | :--- |
| **Ma trận kề (Adjacency Matrix)** | $O(V^2)$ | $O(V)$ | $O(1)$ | Cache cục bộ rất tốt cho ma trận nhỏ ($V \le 1000$). Lãng phí bộ nhớ với đồ thị thưa. Phù hợp cho thuật toán Floyd-Warshall. |
| **Danh sách kề (`std::vector<Edge> adj[]`)** | $O(V + E)$ | $O(\text{deg}(u))$ | $O(\text{deg}(u))$ | Chuẩn mực thực chiến. Cần `adj[u].reserve()` trước nếu biết số bậc để giảm thiểu cấp phát động lại (reallocation). |
| **Static Forward Star (Head/Next array)** | $O(V + E)$ | $O(\text{deg}(u))$ | $O(\text{deg}(u))$ | **Thân thiện phần cứng nhất**: Mảng phẳng liên tục trong bộ nhớ, không tốn overhead của con trỏ hay dynamic vector, tối đa hóa L1/L2 cache hit. |

```cpp
// Static Forward Star Representation (Cực đại hóa Cache Locality)
const int MAXV = 100005;
const int MAXE = 500005;

int head[MAXV], to[MAXE], weight[MAXE], nxt[MAXE], edge_cnt = 0;

void init_graph(int n) {
    std::fill(head, head + n + 1, -1);
    edge_cnt = 0;
}

void add_edge(int u, int v, int w) {
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}
```

---

## 2. 📊 Bảng Quyết Định Giải Thuật & Tiệm Cận (Complexity & Decision Matrix)

| Thuật toán | Tiệm cận thời gian (Time) | Không gian (Space) | Điều kiện áp dụng | Bất biến giải thuật (Loop Invariant) |
| :--- | :---: | :---: | :--- | :--- |
| **BFS (Standard)** | $O(V + E)$ | $O(V)$ | Đồ thị không trọng số hoặc trọng số bằng nhau. | Hàng đợi (Queue) luôn chứa các đỉnh có khoảng cách tăng đơn điệu ($d, d, \dots, d+1$). |
| **0-1 BFS (`std::deque`)** | $O(V + E)$ | $O(V)$ | Cạnh chỉ có trọng số $0$ hoặc $1$. | Đẩy cạnh trọng số 0 lên đầu hàng đợi (`push_front`), cạnh trọng số 1 về đuôi (`push_back`), giữ queue luôn đơn điệu. |
| **Dijkstra (Min-Heap)** | $O((V + E) \log V)$ | $O(V)$ | Trọng số cạnh **không âm** ($w \ge 0$). | Đỉnh $u$ có $d$ nhỏ nhất lấy ra từ heap luôn đạt khoảng cách ngắn nhất tuyệt đối: $dist[u] = \delta(s, u)$. |
| **Bellman-Ford / SPFA** | $O(V \times E)$ | $O(V)$ | Trọng số có thể âm, phát hiện chu trình âm. | Sau $k$ lượt duyệt, mọi đường đi ngắn nhất dùng $\le k$ cạnh đã được tối ưu. |
| **Floyd-Warshall** | $O(V^3)$ | $O(V^2)$ | Mọi cặp đỉnh, $V \le 500$. | Sau bước lặp $k$, $dp[i][j]$ là đường đi ngắn nhất từ $i$ đến $j$ chỉ đi qua các đỉnh trung gian $\{1 \dots k\}$. |
| **Kruskal (DSU)** | $O(E \log E)$ | $O(V + E)$ | Tìm Cây khung nhỏ nhất (MST). | Luôn chọn cạnh có trọng số nhỏ nhất mà không tạo chu trình (nối 2 thành phần liên thông rời rạc). |
| **Prim (Min-Heap)** | $O((V + E) \log V)$ | $O(V)$ | Tìm MST trên đồ thị dày ($E \approx V^2$). | Cây khung con luôn tăng trưởng bằng cách nạp đỉnh gần nhất chưa thuộc cây. |
| **Kahn (Topological Sort)** | $O(V + E)$ | $O(V)$ | Đồ thị có hướng không chu trình (DAG). | Hàng đợi luôn chỉ chứa các đỉnh có bán bậc vào $\text{in\_degree}[u] = 0$. |
| **Tarjan (SCC / Bridges)** | $O(V + E)$ | $O(V)$ | Phân rã thành phần liên thông mạnh / tìm cầu, khớp. | $low[u]$ là chỉ số DFS nhỏ nhất vươn tới được từ cây con gốc $u$ qua tối đa 1 cạnh ngược. |

---

## 3. 🚀 Các Giải Thuật Cốt Lõi (Kèm Code Mẫu C++20 Chuẩn Mực)

### 3.1. Thuật Toán Dijkstra Chuẩn (Xử Lý Tràn Số & Cạnh Đa)
Áp dụng tìm đường đi ngắn nhất từ một đỉnh nguồn tới mọi đỉnh khác với trọng số không âm.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Sử dụng 64-bit integer để phòng chống tràn số (OverFlow Defense: 2^63 - 1)
using ll = long long;
using pll = pair<ll, int>; // {khoảng cách, đỉnh}

const ll INF = 1e18; // Khởi tạo vô cực an toàn tuyệt đối với phép cộng

struct Edge {
    int to;
    ll weight;
};

vector<ll> dijkstra(int n, int start_node, const vector<vector<Edge>>& adj, vector<int>& trace) {
    vector<ll> dist(n + 1, INF);
    trace.assign(n + 1, -1);
    
    // priority_queue tối ưu: Min-Heap
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Bất biến: Nếu đã có đường đi ngắn hơn tới u được xử lý trước đó, bỏ qua
        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            ll w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                trace[v] = u; // Lưu vết đường đi
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

---

### 3.2. 0-1 BFS: Tối Ưu Tuyến Tính $O(V + E)$
Thường gặp trong các bài toán lưới của Samsung SW Test: di chuyển tốn 0 xăng (nếu đi thẳng) hoặc tốn 1 xăng (nếu đổi hướng/bật khiên). Thay thế hoàn hảo cho Dijkstra khi chi phí chỉ là 0 hoặc 1.

```cpp
#include <deque>
#include <vector>

using namespace std;

const int INF = 1e9 + 7;

struct Edge01 {
    int to;
    int weight; // Chỉ có giá trị 0 hoặc 1
};

vector<int> zero_one_bfs(int n, int start, const vector<vector<Edge01>>& adj) {
    vector<int> dist(n + 1, INF);
    deque<int> dq;

    dist[start] = 0;
    dq.push_back(start);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (const auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v); // Cạnh 0 được ưu tiên xử lý trước trong cùng mức
                } else {
                    dq.push_back(v);  // Cạnh 1 xử lý sau
                }
            }
        }
    }
    return dist;
}
```

---

### 3.3. DSU & Thuật Toán Kruskal (Minimum Spanning Tree)
Tập hợp rời rạc (Disjoint Set Union) với 2 kỹ thuật tối ưu cốt lõi: **Nén đường đi (Path Compression)** và **Gộp theo kích thước (Union by Size)**, đạt độ phức tạp tiệm cận gần như hằng số $O(\alpha(N))$.

```cpp
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        sz.assign(n + 1, 1);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;

        // Union by size: Gộp cây nhỏ vào cây lớn
        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
        parent[root_j] = root_i;
        sz[root_i] += sz[root_j];
        return true;
    }
};

struct EdgeKruskal {
    int u, v;
    long long w;
    bool operator<(const EdgeKruskal& other) const {
        return w < other.w;
    }
};

long long kruskal(int n, vector<EdgeKruskal>& edges) {
    sort(edges.begin(), edges.end()); // O(E log E)
    DSU dsu(n);
    long long mst_weight = 0;
    int edges_count = 0;

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst_weight += e.w;
            edges_count++;
            if (edges_count == n - 1) break; // Đã đủ n - 1 cạnh cho cây khung
        }
    }

    return (edges_count == n - 1) ? mst_weight : -1; // -1 nếu đồ thị không liên thông
}
```

---

### 3.4. Thứ Tự Tô-pô & Phát Hiện Chu Trình (Kahn's Algorithm)
Áp dụng cho lập lịch phụ thuộc tiến trình hoặc kiểm tra tính hợp lệ của hệ thống quan hệ.

```cpp
#include <vector>
#include <queue>

using namespace std;

vector<int> kahn_topological_sort(int n, const vector<vector<int>>& adj) {
    vector<int> in_degree(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Nếu số đỉnh lấy ra < n, đồ thị có chứa chu trình (Cycle Detected)
    if (static_cast<int>(topo_order.size()) < n) return {}; 
    return topo_order;
}
```

---

## 4. 🧠 Kỹ Thuật Đồ Thị Samsung SW Test Chuyên Sâu: Multi-State BFS

Trong các đề thi Samsung Professional / Advanced, bài toán thường yêu cầu di chuyển trên mê cung 2D với **chìa khóa / năng lượng / trạng thái phá tường**:
* **Không gian trạng thái**: Đỉnh $u$ được mở rộng thành tuple $(r, c, \text{mask})$.
* **Mặt nạ Bit (Bitmask)**: Nếu có tối đa $K$ loại chìa khóa ($K \le 8$), trạng thái chìa khóa được mã hóa bằng số nguyên `mask` từ $0$ đến $2^K - 1$.
* **Mảng khoảng cách**: `dist[MAXR][MAXC][1 << K]`.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

struct State {
    int r, c, mask, dist;
};

int solve_grid_multistate(int R, int C, const vector<string>& grid) {
    int start_r = -1, start_c = -1;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') {
                start_r = i;
                start_c = j;
            }
        }
    }

    // dist[r][c][mask] lưu số bước nhỏ nhất tới ô (r, c) với tập chìa khóa mask
    vector<vector<vector<int>>> dist(R, vector<vector<int>>(C, vector<int>(1 << 4, -1)));
    queue<State> q;

    dist[start_r][start_c][0] = 0;
    q.push({start_r, start_c, 0, 0});

    while (!q.empty()) {
        auto [r, c, mask, d] = q.front();
        q.pop();

        if (grid[r][c] == 'E') return d; // Đích đến

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            char cell = grid[nr][nc];
            if (cell == '#') continue; // Chướng ngại vật

            int nmask = mask;
            // Nếu là chìa khóa ('a' - 'd')
            if (cell >= 'a' && cell <= 'd') {
                nmask |= (1 << (cell - 'a'));
            }
            // Nếu là cửa ('A' - 'D'), cần có chìa khóa tương ứng
            if (cell >= 'A' && cell <= 'D') {
                if (!(mask & (1 << (cell - 'A')))) continue; // Không có chìa khóa
            }

            if (dist[nr][nc][nmask] == -1) {
                dist[nr][nc][nmask] = d + 1;
                q.push({nr, nc, nmask, d + 1});
            }
        }
    }

    return -1; // Không tìm được đường đến đích
}
```

---

## 5. 🛡️ Checklist Phòng Vệ Biên & Kiểm Thử Đối Nghịch (Adversarial Testing)

Trước khi submit bài toán đồ thị lên hệ thống chấm, luôn kiểm tra các trường hợp suy biến sau:

1. **Trường hợp suy biến đỉnh**:
   * $V = 1, E = 0$: Đỉnh nguồn trùng đỉnh đích ($S = T$). Khoảng cách bằng $0$, không phải `INF`.
   * $V = 0$: Xử lý mảng rỗng ngay lập tức.
2. **Đồ thị không liên thông**:
   * Kiểm tra điều kiện `dist[T] == INF` để xuất `-1` thay vì in ra giá trị rác.
   * Với MST (Kruskal), kiểm tra xem số cạnh được chọn có đủ $V - 1$ cạnh hay không.
3. **Đa cạnh và Khuyên (Self-loops & Multiple edges)**:
   * Nếu bài toán cho nhiều cạnh nối cùng cặp $(u, v)$ với các trọng số khác nhau, ma trận kề chỉ lưu $\min(w)$, danh sách kề xử lý tự nhiên qua `priority_queue`.
4. **Phòng chống tràn số nguyên ($2^{63} - 1$)**:
   * Tuyệt đối không dùng `int` cho tổng chi phí đường đi. Dùng `long long` cho `dist[]` và `INF = 1e18`.
   * Tránh cộng `INF + w` gây tràn số âm (`dist[u] + w` khi `dist[u] == INF`).

---

## 6. 🔗 Mã Nguồn Minh Họa Trực Tiếp Trong Kho

* **[Dijkstra.cpp](Dijkstra.cpp)**: Cài đặt thuật toán Dijkstra tìm đường đi ngắn nhất đồ thị trọng số không âm kèm mảng truy vết `trace[]`.
* **[bfs.cpp](bfs.cpp)**: Cài đặt BFS duyệt đồ thị và đếm thành phần liên thông.
* **[CVRP_optimize.cpp](CVRP_optimize.cpp)** & **[forhg.cpp](forhg.cpp)**: Ứng dụng mô hình đồ thị chi phí vào bài toán tối ưu hóa hành trình xe buýt / xe giao hàng.
