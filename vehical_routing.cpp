#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, K, Q;
int d[15];
int c[15][15];
bool visited[15];
int load[6];
int start_node[6]; // Lưu khách hàng đầu tiên mà xe k ghé thăm
int ans = 1e9;
int cmin = 1e9;

// k: xe hiện tại đang chạy (1 đến K)
// curr_node: vị trí hiện tại của xe k (bắt đầu từ 0)
// clients_visited: tổng số khách hàng đã được phục vụ
// current_cost: tổng chi phí quãng đường đã đi
void Try(int k, int curr_node, int clients_visited, int current_cost) {
    // Nếu đã giao hết cho n khách hàng
    if (clients_visited == n) {
        // Cộng thêm chi phí từ khách hàng cuối cùng quay về kho
        ans = min(ans, current_cost + c[curr_node][0]);
        return;
    }
    
    // Đánh giá nhánh cận (Branch and Bound)
    // Cần đi ít nhất (n - clients_visited) cạnh để tới các khách hàng còn lại 
    // và 1 cạnh để quay về kho. Tổng cộng cần ít nhất (n - clients_visited + 1) cạnh.
    if (current_cost + (n - clients_visited + 1) * cmin >= ans) return;

    // Khử đối xứng (Symmetry breaking) để chống TLE:
    // Nếu xe hiện tại đang ở kho (chuẩn bị chọn khách đầu tiên), 
    // nó phải chọn khách có index > khách đầu tiên của xe trước đó.
    int start_v = 1;
    if (curr_node == 0 && k > 1) {
        start_v = start_node[k - 1] + 1;
    }

    // Lựa chọn 1: Xe k tiếp tục đi giao cho một khách hàng v chưa được thăm
    for (int v = start_v; v <= n; ++v) {
        if (!visited[v] && load[k] + d[v] <= Q) {
            visited[v] = true;
            load[k] += d[v];
            
            // Nếu đây là khách đầu tiên của xe k, ghi nhận lại để khử đối xứng cho xe sau
            if (curr_node == 0) start_node[k] = v;
            
            Try(k, v, clients_visited + 1, current_cost + c[curr_node][v]);
            
            // Backtrack
            visited[v] = false;
            load[k] -= d[v];
        }
    }

    // Lựa chọn 2: Đóng chuyến xe hiện tại, cho xe k về kho và khởi hành xe k+1
    // Điều kiện: Xe k phải giao ít nhất 1 đơn (curr_node != 0) mới có ý nghĩa. 
    // Nếu xe k đi tay không thì không cần xét xe k+1 làm gì.
    if (k < K && curr_node != 0) {
        Try(k + 1, 0, clients_visited, current_cost + c[curr_node][0]);
    }
}

int main() {
    // Tối ưu I/O cực mạnh
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n >> K >> Q)) return 0;
    
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> c[i][j];
            // Tìm cạnh có trọng số nhỏ nhất (> 0) để làm cmin cho nhánh cận
            if (i != j && c[i][j] < cmin) {
                cmin = c[i][j];
            }
        }
    }
    
    // Gọi đệ quy: bắt đầu từ xe 1, đang ở kho 0, đã thăm 0 khách, chi phí 0
    Try(1, 0, 0, 0);
    
    cout << ans << "\n";
    return 0;
}