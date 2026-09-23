# Data-Structures-Algorithms-CPA377

A rigorous repository of advanced Data Structures & Algorithms tailored for Samsung SW Competency Test (Advanced/Professional) and Competitive Programming. Implementing high-performance solutions in C++ with clean architecture, optimal resource management, and deep complexity analysis under strict constraints.

## 👤 About Me
- **Author**: Đặng Minh Quân
- **Institution**: Hanoi University of Science and Technology (HUST)
- **Current CPA**: 3.77/4.0 (Ranked: High Distinction)
- **Expected Graduation**: 2028

## 🎯 Focus Areas
Mastering competitive programming and problem-solving patterns tailored to algorithmic requirements:
* Backtracking & Branch and Bound (Combinatorial Optimization)
* Dynamic Programming (Optimal Substructure & State Optimization)
* Graph Theory (Shortest Path, BFS, DFS)
* Advanced Data Structures (Segment Tree, Monotonic Stack, Custom Linked Lists)

---

## 📊 Progress Dashboard
* **Total Problems / Implementations**: 36 modules
* **Backtracking & Branch-and-Bound**: 8 problems
* **Dynamic Programming**: 6 problems
* **Data Structures (Segment Tree, Stack, Linked List)**: 8 implementations
* **Graph Theory & Greedy**: 6 problems
* **Database & Utilities**: 3 SQL schemas + BigInt & text search

---

## 📑 Algorithmic Matrix & Implementations

### 1. 🧩 Nhánh & Cận / Quay Lui (Branch and Bound & Backtracking)
* **[CVRP_optimize.cpp](CVRP_optimize.cpp)** & **[vehical_routing.cpp](vehical_routing.cpp)**: Bài toán định tuyến xe có tải trọng (Capacitated Vehicle Routing Problem - CVRP) với $K$ xe và tải trọng $Q$. Cận dưới: $f + c_{min} \times (N - \text{visited} + 1) \ge f^*$.
* **[forhg.cpp](forhg.cpp)**: Xe buýt đón/trả khách có sức chứa (Capacitated Bus - CBus). Ràng buộc đón trước trả và tải trọng tức thời $\le K$.
* **[balanced_courses_assignments.cpp](balanced_courses_assignments.cpp)**: Phân công khóa học (Balanced Academic Curriculum / BACP) nhằm cân bằng tải tối đa cho giảng viên với ràng buộc môn học xung đột.
* **[Cut_Material.cpp](Cut_Material.cpp)**: Xếp $n$ mảnh chữ nhật (có thể xoay $90^\circ$) vào tấm vật liệu $W \times H$.
* **[Sudoku.cpp](Sudoku.cpp)**: Giải Sudoku chuẩn $9 \times 9$.
* **[digits_ICT_K62_HUST.cpp](digits_ICT_K62_HUST.cpp)**: Tìm cấu hình chữ số phân biệt thỏa mãn phương trình số học `ICT - K62 + HUST = N`.
* **[binary_sequnence.cpp](binary_sequnence.cpp)**, **[backtracking.cpp](backtracking.cpp)**: Cấu hình tổ hợp và sinh nhị phân.

### 2. ⚡ Quy Hoạch Động (Dynamic Programming)
* **[DP_SegmentTree.cpp](DP_SegmentTree.cpp)**: Tối ưu hóa DP bằng Segment Tree ($O(N \log N)$), tính $DP[i] = a[i] + \max_{j \in [i-L_2, i-L_1]} DP[j]$.
* **[LIS.cpp](LIS.cpp)**: Dãy con tăng dài nhất (Longest Increasing Subsequence).
* **[LCS_dp_2D.cpp](LCS_dp_2D.cpp)**: Xâu con chung dài nhất 2D (Longest Common Subsequence).
* **[max_length_even_subsequence.cpp](max_length_even_subsequence.cpp)**: Dãy con liên tiếp có tổng chẵn dài nhất.
* **[grid_DP_advanced.cpp](grid_DP_advanced.cpp)** & **[tesss.cpp](tesss.cpp)**: Quy hoạch động và đường đi trên ma trận lưới 2D.

### 3. 🏗️ Cấu Trúc Dữ Liệu Nâng Cao (Core Data Structures)
* **[segmentTree.cpp](segmentTree.cpp)**, **[review_segmentTree.cpp](review_segmentTree.cpp)**, **[update_getMax_SegmentTree.cpp](update_getMax_SegmentTree.cpp)**: Cây phân đoạn (Segment Tree) hỗ trợ cập nhật điểm (Point Update) và truy vấn đoạn cực đại (Range Maximum Query) trong $O(\log N)$.
* **[Largest_area.cpp](Largest_area.cpp)**: Tìm diện tích hình chữ nhật lớn nhất trong biểu đồ cột (Largest Rectangle in Histogram) bằng Ngăn xếp đơn điệu (Monotonic Stack) trong $O(N)$.
* **[LinkedList.cpp](LinkedList.cpp)** & **[test_LinkedList.cpp](test_LinkedList.cpp)**: Cài đặt và kiểm thử danh sách liên kết đơn tổng quát (Template Singly Linked List) chuẩn C++ OOP.

### 4. 🕸️ Đồ Thị, Tham Lam & Tìm Kiếm Nhị Phân (Graph, Greedy & Binary Search)
* **[1_Graph_Theory](1_Graph_Theory)**: Cẩm nang toàn diện Lý thuyết đồ thị (Graph Theory Handbook) - Ma trận độ phức tạp, Dijkstra, 0-1 BFS, Kruskal DSU, Kahn Topo sort, Multi-State BFS chuyên sâu cho Samsung SW Test.
* **[Dijkstra.cpp](Dijkstra.cpp)**: Đường đi ngắn nhất trên đồ thị trọng số dương sử dụng Min-Heap (`std::priority_queue`) với độ phức tạp $O((V + E) \log V)$.
* **[bfs.cpp](bfs.cpp)**: Duyệt đồ thị theo chiều rộng (Breadth-First Search).
* **[max_distance_subset.cpp](max_distance_subset.cpp)**: Tìm kiếm nhị phân trên không gian nghiệm (Binary Search on Answer) cho bài toán Aggressive Cows.
* **[Job_scheduling.cpp](Job_scheduling.cpp)** & **[planning.cpp](planning.cpp)**: Lập lịch công việc tối đa hóa lợi nhuận (Interval / Deadline Job Scheduling) theo chiến lược Tham lam (Greedy).

### 5. 🛠️ Xử Lý Số Lớn, Chuỗi & Cơ Sở Dữ Liệu
* **[Bai2.13.cpp](Bai2.13.cpp)**: Struct số nguyên lớn (`bigNum`) hỗ trợ toán tử số học.
* **[bai4.10.cpp](bai4.10.cpp)**: Tính toán tần suất từ và độ tương đồng văn bản (TF-IDF / Vector Space Model).
* **[.vscode/Database_practice/](.vscode/Database_practice/)**: Thực hành cơ sở dữ liệu quan hệ (`QLBaiDauXe.sql`, `QLGiaoDuc.sql`, `QLVanDon.sql`).

---

## 🛠 Hướng Dẫn Biên Dịch & Chạy

Sử dụng trình biên dịch hỗ trợ **C++20** (GCC hoặc Clang):

```bash
# Biên dịch một tệp thuật toán bất kỳ (ví dụ: Cut_Material.cpp)
clang++ -std=c++20 -O2 Cut_Material.cpp -o Cut_Material

# Chạy tệp thực thi
./Cut_Material
```

Các tệp nhị phân và bundle debug `.dSYM` được tự động loại bỏ bởi [.gitignore](.gitignore) khi đồng bộ Git.
