#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> dat(1);
vector<vector<vector<int>>> v;
int n, m, l;

int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};

const int wall = 1 << 4;

bool valid(int x, int y) { return 0 <= x && x < m && 0 <= y && y < n; }

void print(int t) {
    return;
    for (auto &&r : dat[t]) {
        for (auto &&c : r) {
            cout << (c ? '#' : '.');
            // cout << c << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

int bfs(int sx, int sy, int st, int ty) {
    queue<tuple<int, int, int>> q;  // x,y,t
    for (auto &&d : v) {
        for (auto &&r : d) {
            r.assign(m, 0);
        }
    }
    q.push({sx, sy, st});
    v[st % l][sy][sx] = 0;
    while (!q.empty()) {
        auto [x, y, t] = q.front();
        q.pop();
        int tt = (t + 1) % l;
        for (size_t d = 0; d < 4; d++) {
            int xx = x + dx[d], yy = y + dy[d];
            if (valid(xx, yy) && !dat[tt][yy][xx] && !v[tt][yy][xx]) {
                if (yy == ty) {
                    return t + 1;
                }
                q.push({xx, yy, t + 1});
                v[tt][yy][xx] = 1;
            }
        }
        if (!dat[tt][y][x] && !v[tt][y][x]) {
            q.push({x, y, t + 1});
        }
    }
    throw -1;
}

int main() {
    ifstream fin("in");
    string line;
    while (fin >> line) {
        dat[0].push_back({});
        auto &row = dat[0].back();
        for (auto &&c : line) {
            switch (c) {
                case '^':
                    row.push_back(1 << 0);
                    break;
                case '>':
                    row.push_back(1 << 1);
                    break;
                case 'v':
                    row.push_back(1 << 2);
                    break;
                case '<':
                    row.push_back(1 << 3);
                    break;
                case '#':
                    row.push_back(wall);
                    break;
                case '.':
                    row.push_back(0);
                    break;
                default:
                    throw -1;
            }
        }
    }
    n = dat[0].size();
    m = dat[0][0].size();
    l = lcm(n, m);
    v.resize(l, {});
    for (auto &&d : v) {
        d.resize(n, {});
        for (auto &&r : d) {
            r.resize(m, 0);
        }
    }
    print(0);
    for (size_t i = 1; i < lcm(n, m); i++) {
        dat.push_back({});
        auto &cur = dat[i], &last = dat[i - 1];
        cur.resize(n, {});
        for (size_t j = 0; j < n; j++) {
            cur[j].resize(m, {});
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                switch (last[j][k]) {
                    case 0:
                    case wall:
                        cur[j][k] |= last[j][k];
                        break;
                    default:
                        for (size_t d = 0; d < 4; d++) {
                            if (last[j][k] & 1 << d) {
                                int y = (j + dy[d] + n - 3) % (n - 2) + 1,
                                    x = (k + dx[d] + m - 3) % (m - 2) + 1;
                                cur[y][x] |= 1 << d;
                            }
                        }
                        break;
                }
            }
        }
        print(i);
    }
    int sx = find(dat[0][0].begin(), dat[0][0].end(), 0) - dat[0][0].begin(),
        tx = find(dat[0][n - 1].begin(), dat[0][n - 1].end(), 0) -
             dat[0][n - 1].begin();
    int t = bfs(sx, 0, 0, n - 1);
    t = bfs(tx, n - 1, t, 0);
    cout << bfs(sx, 0, t, n - 1) << endl;
}