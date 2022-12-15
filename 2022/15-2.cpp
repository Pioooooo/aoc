#include <bits/stdc++.h>
using namespace std;

const long long N = 4000000;
vector<pair<int, int>> imp[N + 1];

int main() {
    ifstream fin("in");
    string word;
    char c;
    int xs, ys, xb, yb;
    while (fin >> word >> word >> c >> c >> xs >> word >> c >> c >> ys >>
           word >> word >> word >> word >> word >> c >> c >> xb >> word >> c >>
           c >> yb) {
        int d = abs(xb - xs) + abs(yb - ys);
        for (int i = 0; i <= N; i++) {
            int s = d - abs(i - ys);
            if (s < 0) {
                continue;
            }
            imp[i].push_back({xs - s, xs + s});
        }
    }
    for (int j = 0; j <= N; j++) {
        auto &row = imp[j];
        sort(row.begin(), row.end(), [](auto &p1, auto &p2) {
            return p1.first < p2.first ||
                   p1.first == p2.first && p1.second < p2.second;
        });
        int x1 = row[0].first, x2 = row[0].second;
        for (size_t i = 1; i < row.size(); i++) {
            while (i < row.size()) {
                if (row[i].first > x2 + 1 && x2 + 1 < N) {
                    cout << N * (x2 + 1) + j << endl;
                    return 0;
                }
                x2 = max(x2, row[i].second);
                i++;
            }
            if (i + 1 == row.size()) {
                break;
            }
            x1 = row[i + 1].first;
            x2 = row[i + 1].second;
        }
    }
}