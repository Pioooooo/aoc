#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    array<int, 6> b;
    char c;
    vector<array<int, 6>> dat;
    while (fin >> b[0] >> c >> b[1] >> c >> b[2] >> c >> b[3] >> c >> b[4] >>
           c >> b[5]) {
        dat.push_back(b);
    }
    ranges::sort(dat, [](auto a, auto b) {
        if (a[2] != b[2]) {
            return a[2] < b[2];
        }
        if (a[1] != b[1]) {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    });
    int n = dat.size();
    vector<set<int>> on(n), support(n);
    vector<int> h(n);
    map<pair<int, int>, int> top;
    for (int i = 0; i < n; i++) {
        auto [x1, y1, z1, x2, y2, z2] = dat[i];
        h[i] = 0;
        auto& bottom = on[i];
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                auto it = top.find({x, y});
                if (it != top.end()) {
                    if (h[i] == h[it->second]) {
                        bottom.insert(it->second);
                    } else if (h[it->second] > h[i]) {
                        h[i] = h[it->second];
                        bottom = {it->second};
                    }
                }
            }
        }
        h[i] += z2 - z1 + 1;
        for (auto j : bottom) {
            support[j].insert(i);
        }
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                top[{x, y}] = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        queue<int> q{{i}};
        auto o = on;
        while (!q.empty()) {
            int j = q.front();
            q.pop();
            for (auto k : support[j]) {
                o[k].erase(j);
                if (o[k].empty()) {
                    q.push(k);
                    sum++;
                }
            }
        }
    }
    cout << sum << endl;
}
