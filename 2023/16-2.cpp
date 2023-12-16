#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> dat;
    while (getline(fin, line)) {
        dat.push_back(line);
    }
    int n = dat.size(), m = dat[0].size();
    auto calc = [&](int x0, int y0, int d) {
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<tuple<int, int, int>> q;
        q.emplace(x0, y0, d);
        while (!q.empty()) {
            auto [x, y, d] = q.front();
            q.pop();
            auto xx = x + dx[d], yy = y + dy[d];
            if (xx < 0 || xx >= m || yy < 0 || yy >= n ||
                vis[yy][xx] & 1 << d) {
                continue;
            }
            vis[yy][xx] |= 1 << d;
            switch (dat[yy][xx]) {
                case '.':
                    vis[yy][xx] |= 1 << ((d + 2) % 4);
                    q.emplace(xx, yy, d);
                    break;
                case '/':
                    vis[yy][xx] |= 1 << (3 - d);
                    q.emplace(xx, yy, d ^ 1);
                    break;
                case '\\':
                    vis[yy][xx] |= 1 << (d ^ 1);
                    q.emplace(xx, yy, 3 - d);
                    break;
                case '|':
                    if (d % 2 == 1) {
                        vis[yy][xx] |= 1 << 0 + 1 << 2;
                        q.emplace(xx, yy, 0);
                        q.emplace(xx, yy, 2);
                    } else {
                        vis[yy][xx] |= 1 << ((d + 2) % 4);
                        q.emplace(xx, yy, d);
                    }
                    break;
                case '-':
                    if (d % 2 == 0) {
                        vis[yy][xx] |= 1 << 1 + 1 << 3;
                        q.emplace(xx, yy, 1);
                        q.emplace(xx, yy, 3);
                    } else {
                        vis[yy][xx] |= 1 << ((d + 2) % 4);
                        q.emplace(xx, yy, d);
                    }
                    break;
                default:
                    unreachable();
            }
        }
        sum = max(sum, ranges::fold_left(
                           vis | views::transform([](const auto& a) -> int {
                               return ranges::count_if(a,
                                                       [](int b) { return b; });
                           }),
                           0, plus{}));
    };
    for (int j = 0; j < n; j++) {
        calc(-1, j, 1);
        calc(m, j, 3);
    }
    for (int i = 0; i < m; i++) {
        calc(i, -1, 2);
        calc(i, n, 0);
    }
    cout << sum << endl;
}
