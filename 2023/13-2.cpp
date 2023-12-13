#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    while (true) {
        vector<string> dat;
        while (getline(fin, line) && !line.empty()) {
            dat.push_back(line);
        }
        if (dat.empty()) {
            break;
        }
        int n = dat.size(), m = dat[0].size();
        vector<int> row(n - 1), col(m - 1);
        vector<bool> rr(n - 1), cc(m - 1);
        iota(row.begin(), row.end(), 1);
        iota(col.begin(), col.end(), 1);
        
        // removed range usages due to
        // https://stackoverflow.com/questions/64199664/why-c-ranges-transform-filter-calls-transform-twice-for-values-that-match
        for (int i = 0; i < n; i++) {
            vector<int> ret;
            for (auto &&j : col) {
                bool flag = true;
                for (int k = 0; k + 1 <= j && j + k < m; k++) {
                    if (dat[i][j - k - 1] != dat[i][j + k]) {
                        if (cc[j]) {
                            flag = false;
                            break;
                        } else {
                            cc[j] = true;
                        }
                    }
                }
                if (flag) {
                    ret.push_back(j);
                }
            }
            col = ret;
        }
        sum += ranges::fold_left(
            col | views::filter([&](int j) { return cc[j]; }), 0, plus{});

        for (int j = 0; j < m; j++) {
            vector<int> ret;
            for (auto &&i : row) {
                bool flag = true;
                for (int k = 0; k + 1 <= i && i + k < n; k++) {
                    if (dat[i - k - 1][j] != dat[i + k][j]) {
                        if (rr[i]) {
                            flag = false;
                            break;
                        } else {
                            rr[i] = true;
                        }
                    }
                }
                if (flag) {
                    ret.push_back(i);
                }
            }
            row = ret;
        }
        sum += 100 * ranges::fold_left(
                         row | views::filter([&](int i) { return rr[i]; }), 0,
                         plus{});
    }
    cout << sum << endl;
}
