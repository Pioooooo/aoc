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
        iota(row.begin(), row.end(), 1);
        iota(col.begin(), col.end(), 1);
        sum += ranges::fold_left(
            ranges::fold_left(
                views::iota(0, n), col,
                [&](auto r, int i) {
                    auto v = r | views::filter([&](int j) {
                                 for (int k = 0; k + 1 <= j && j + k < m; k++) {
                                     if (dat[i][j - k - 1] != dat[i][j + k]) {
                                         return false;
                                     }
                                 }
                                 return true;
                             });
                    return vector(v.begin(), v.end());
                }),
            0, plus{});
        sum +=
            100 *
            ranges::fold_left(
                ranges::fold_left(
                    views::iota(0, m), row,
                    [&](vector<int> r, int j) {
                        auto v =
                            r | views::filter([&](int i) {
                                for (int k = 0; k + 1 <= i && i + k < n; k++) {
                                    if (dat[i - k - 1][j] != dat[i + k][j]) {
                                        return false;
                                    }
                                }
                                return true;
                            });
                        return vector(v.begin(), v.end());
                    }),
                0, plus{});
    }
    cout << sum << endl;
}
