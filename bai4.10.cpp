#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> split(const string &s) {
    vector<string> res;
    stringstream ss(s);
    string tok;
    while (getline(ss, tok, ',')) {
        if (!tok.empty()) res.push_back(tok);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);

    map<string, int> id;
    int id_cnt = 0;
    auto get_id = [&](const string &w) {
        if (id.find(w) == id.end()) id[w] = id_cnt++;
        return id[w];
    };

    vector<vector<int>> f(n);
    vector<int> mx_f(n, 0);

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        vector<string> words = split(s);
        
        map<int, int> cnt;
        for (const string &w : words) cnt[get_id(w)]++;

        int cur_mx = 0;
        for (auto const& [t, c] : cnt) cur_mx = max(cur_mx, c);
        mx_f[i] = cur_mx;

        f[i].resize(id_cnt, 0);
        for (auto const& [t, c] : cnt) f[i][t] = c;
    }

    vector<int> df(id_cnt, 0);
    for (int t = 0; t < id_cnt; ++t) {
        for (int d = 0; d < n; ++d) {
            if (t < f[d].size() && f[d][t] > 0) df[t]++;
        }
    }

    vector<double> idf(id_cnt, 0.0);
    for (int t = 0; t < id_cnt; ++t) {
        if (df[t] > 0) idf[t] = log2((double)n / df[t]);
    }

    int q;
    if (!(cin >> q)) return 0;
    getline(cin, dummy);

    while (q--) {
        string s;
        getline(cin, s);
        vector<string> q_words = split(s);

        int best_d = 1;
        double max_s = -1.0;

        for (int d = 0; d < n; ++d) {
            double cur_s = 0.0;
            for (const string &w : q_words) {
                if (id.find(w) == id.end()) continue;
                int t = id[w];
                if (t < f[d].size() && f[d][t] > 0) {
                    double tf = 0.5 + 0.5 * ((double)f[d][t] / mx_f[d]);
                    cur_s += tf * idf[t];
                }
            }

            if (cur_s > max_s) {
                max_s = cur_s;
                best_d = d + 1;
            }
        }
        cout << best_d << "\n";
    }

    return 0;
}