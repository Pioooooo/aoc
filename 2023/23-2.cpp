#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> dat;
    while (getline(fin, line)) {
        dat.push_back(line);
    }
    vector<vector<bool>> vis(dat.size(), vector<bool>(dat[0].size(), false));
    int n = dat.size(), m = dat[0].size();
    pair<int, int> s = {0, dat[0].find('.')}, t = {n - 1, dat[n - 1].find('.')};
    map<pair<int, int>, map<pair<int, int>, int>> dis;
    set<pair<int, int>> nodes{s, t};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dat[i][j] == '#') {
                continue;
            }
            int b = 0;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m ||
                    dat[nx][ny] == '#') {
                    continue;
                }
                b++;
            }
            if (b > 2) {
                nodes.emplace(i, j);
            }
        }
    }
    for (auto& [x, y] : nodes) {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || dat[nx][ny] == '#' ||
                vis[nx][ny]) {
                continue;
            }
            int l = 1, d = i;
            while (!nodes.contains({nx, ny})) {
                l++;
                vis[nx][ny] = true;
                for (int j = 0; j < 4; j++) {
                    if (j == (d ^ 1)) {
                        continue;
                    }
                    int nnx = nx + dx[j], nny = ny + dy[j];
                    if (nnx < 0 || nnx >= n || nny < 0 || nny >= m ||
                        dat[nnx][nny] == '#') {
                        continue;
                    }
                    nx = nnx, ny = nny, d = j;
                    break;
                }
            }
            dis[{x, y}][{nx, ny}] = max(dis[{x, y}][{nx, ny}], l);
            dis[{nx, ny}][{x, y}] = max(dis[{nx, ny}][{x, y}], l);
        }
    }
    set<pair<int, int>> vis2;
    function<int(int, int)> dfs = [&](int x, int y) {
        vis2.emplace(x, y);
        int res = -1;
        for (auto& [k, v] : dis[{x, y}]) {
            auto& [nx, ny] = k;
            if (t == k) {
                res = v;
                break;
            }
            if (vis2.contains(k)) {
                continue;
            }
            int d = dfs(nx, ny);
            if (d == -1) {
                continue;
            }
            res = max(res, d + v);
        }
        vis2.erase({x, y});
        return res;
    };
    cout << dfs(s.first, s.second) << endl;
}
