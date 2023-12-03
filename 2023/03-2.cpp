#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> engine;
    while (getline(fin, line)) {
        engine.push_back(line);
    }
    int n = engine.size(), m = engine[0].size();
    vector<vector<pair<int, int>>> gears(n, vector<pair<int, int>>(m));

    auto handle = [&](int i, int j, int cur) {
        if (engine[i][j] == '*') {
            gears[i][j].first++;
            if (gears[i][j].second == 0) {
                gears[i][j].second = cur;
            } else {
                gears[i][j].second *= cur;
            }
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isdigit(engine[i][j])) {
                continue;
            }
            int cur = engine[i][j] - '0', l = 0;
            while (j + (++l) < m) {
                if (!isdigit(engine[i][j + l])) {
                    break;
                }
                cur = cur * 10 + engine[i][j + l] - '0';
            }
            bool found = false;
            if (i > 0) {
                for (int k = max(0, j - 1); k < min(m, j + l + 1); k++) {
                    handle(i - 1, k, cur);
                }
            }
            if (!found && i + 1 < n) {
                for (int k = max(0, j - 1); k < min(m, j + l + 1); k++) {
                    handle(i + 1, k, cur);
                }
            }
            if (!found && j > 0 && engine[i][j - 1] == '*') {
                handle(i, j - 1, cur);
            }
            if (!found && j + l < m && engine[i][j + l] == '*') {
                handle(i, j + l, cur);
            }
            j += l;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (gears[i][j].first == 2) {
                sum += gears[i][j].second;
            }
        }
    }

    cout << sum << endl;
}