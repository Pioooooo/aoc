#include <bits/stdc++.h>
using namespace std;

const int y = 2000000;

int main() {
    ifstream fin("in");
    string word;
    char c;
    int xs, ys, xb, yb;
    vector<pair<int, int>> imp;
    set<int> b;
    while (fin >> word >> word >> c >> c >> xs >> word >> c >> c >> ys >>
           word >> word >> word >> word >> word >> c >> c >> xb >> word >> c >>
           c >> yb) {
        int d = abs(xb - xs) + abs(yb - ys);
        int s = d - abs(y - ys);
        if (s < 0) {
            continue;
        }
        imp.push_back({xs - s, xs + s});
        if (yb == y) {
            b.insert(xb);
        }
    }
    if (imp.empty()) {
        cout << 0 << endl;
        return 0;
    }
    sort(imp.begin(), imp.end(), [](auto &p1, auto &p2) {
        return p1.first < p2.first ||
               p1.first == p2.first && p1.second < p2.second;
    });
    int x1 = imp[0].first, x2 = imp[0].second, ans = -b.size();
    for (size_t i = 1; i < imp.size(); i++) {
        while (i < imp.size() && imp[i].first <= x2) {
            x2 = max(x2, imp[i].second);
            i++;
        }
        ans += x2 - x1 + 1;
        if (i + 1 == imp.size()) {
            break;
        }
        x1 = imp[i + 1].first;
        x2 = imp[i + 1].second;
    }
    cout << ans << endl;
}