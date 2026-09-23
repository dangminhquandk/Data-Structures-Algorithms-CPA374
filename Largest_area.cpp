#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

int find_max_area(vector<int>& height) {
    stack<int> st;
    int max_area = 0;
    int m = height.size();

    for (int i = 0; i <= m; ++i) {
        int current_height = (i == m ? 0 : height[i]);
        
        while(!st.empty() && current_height < height[st.top()]) {
            int h = height[st.top()];
            st.pop();

            int width = (st.empty() ? i : i - st.top() - 1);

            max_area = max(max_area, h * width);
        }
        st.push(i);
    }

    return max_area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    int n, m; cin >> n >> m;
    vector<int> height(m, 0);
    int global_max_area = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            int val; cin >> val;
            if (val == 1) height[j]++;
            else height[j] = 0;
        }

        global_max_area = max(global_max_area, find_max_area(height));
    }
    cout << global_max_area << endl;
    return 0;
}