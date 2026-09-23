#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct bigNum {
    char sign; // '0' la am, '1' la duong
    string num;
};

bigNum operator * (const bigNum& a, const bigNum& b) {
    // 1. Nhan 2 chuoi so duong
    // 2. sign moi = (a.sign == b.sign) ? '1' : '0'
    // return ket qua
    bigNum res; return res;
}

bigNum operator + (const bigNum& a, const bigNum& b) {
    // Kiem tra dau de biet la phep cong thuc su hay phep tru
    // return ket qua
    bigNum res; return res;
}

bigNum operator - (const bigNum& a, const bigNum& b) {
    // Kiem tra dau tuong tu de dao nguoc thanh phep cong/tru
    // return ket qua
    bigNum res; return res;
}

int main() {
    string str_a, str_b;
    if (cin >> str_a >> str_b) {
        bigNum a = {str_a[0], str_a.substr(1)};
        bigNum b = {str_b[0], str_b.substr(1)};

        // Tinh a * b - 3 * a + 4 * b
        // bigNum c3 = {"1", "3"};
        // bigNum c4 = {"1", "4"};
        // bigNum ans = (a * b) - (c3 * a) + (c4 * b);

        // cout << ans.sign << ans.num << endl;
    }
    return 0;
}