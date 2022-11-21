#include <bits/stdc++.h>
using namespace std;

int dat[100][100], dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}, x, y = 0,
                   v[100][100];

bool between(int l, int r, int x) { return l <= x && x < r; }

int bfs(int i, int j) {
    queue<pair<int, int>> q;
    q.push({j, i});
    v[j][i] = 1;
    int ret = 1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (size_t k = 0; k < 4; k++) {
            int a = p.first + dy[k], b = p.second + dx[k];
            if (between(0, y, a) && between(0, x, b) && !v[a][b]) {
                ret++;
                q.push({a, b});
                v[a][b] = 1;
            }
        }
    }
    return ret;
}

int main() {
    ifstream fin("in");
    string line;
    while (getline(fin, line)) {
        x = line.length() - 1;
        for (size_t i = 0; i < x; i++) {
            dat[y][i] = line[i] - '0';
            v[y][i] = dat[y][i] == 9;
        }
        y++;
    }
    vector<int> sz;
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            if (!v[j][i]) {
                sz.push_back(bfs(i, j));
            }
        }
    }
    sort(sz.rbegin(), sz.rend());
    cout << sz[0] * sz[1] * sz[2] << endl;
}