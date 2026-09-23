#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    string a, b;
    cin >> a >> b;
    
    int a_size = a.size();
    int b_size = b.size();
    
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    
    vector<int> num_a, num_b;
    for (char c : a) num_a.push_back(c - '0');
    for (char c : b) num_b.push_back(c - '0');

    int i = 0;
    int temp;
    int carrying = 0;
    vector<int> result;
    while (i < a_size || i < b_size || carrying) {
        temp = carrying;
        if (i < a_size)  temp += num_a[i];
        if (i < b_size)  temp += num_b[i];
        result.push_back(temp % 10);
        carrying = temp / 10;
        i++;
    }
    for (int i = result.size() - 1; i >= 0; i--) cout << result[i];
    cout << endl;
    return 0;
}