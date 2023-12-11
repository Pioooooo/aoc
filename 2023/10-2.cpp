#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
map<char, pair<int, int>> dir = {
    {'|', {0, 1}},
    {'-', {2, 3}},
    {'L', {1, 2}},
    {'J', {1, 3}},
    {'7', {0, 3}},
    {'F', {0, 2}},
};

int main() {
    ifstream fin("in");
    int ans = 0;
    string line;
    vector<string> pipes;
    vector<vector<int>> distance;
    queue<tuple<int, int, int>> q;
    while (getline(fin, line)) {
        pipes.push_back(line);
        distance.push_back(vector<int>(line.size(), -1));
        if (line.find('S') != string::npos) {
            q.push({pipes.size() - 1, line.find('S'), -1});
            distance.back()[line.find('S')] = 0;
        }
    }

    int n = pipes.size(), m = pipes[0].size();
    auto step = [&](int x, int y, int i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            return;
        }
        if (!dir.contains(pipes[nx][ny])) {
            return;
        }
        auto [d1, d2] = dir[pipes[nx][ny]];
        if (d1 == (i ^ 1) || d2 == (i ^ 1)) {
            if (distance[nx][ny] == -1) {
                q.push({nx, ny, i});
                distance[nx][ny] = distance[x][y] + 1;
            }
        }
    };

    auto [x, y, d] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
        step(x, y, i);
    }

    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();
        auto [d1, d2] = dir[pipes[x][y]];
        if (d1 != (d ^ 1)) {
            step(x, y, d1);
        } else {
            step(x, y, d2);
        }
    }

    vector<vector<int>> vis(2 * n + 1, vector<int>(2 * m + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vis[2 * i + 1][2 * j + 1] = distance[i][j] != -1;
            if (vis[2 * i + 1][2 * j + 1] && dir.contains(pipes[i][j])) {
                auto [d1, d2] = dir[pipes[i][j]];
                vis[2 * i + 1 + dx[d1]][2 * j + 1 + dy[d1]] = 1;
                vis[2 * i + 1 + dx[d2]][2 * j + 1 + dy[d2]] = 1;
            }
        }
    }

    queue<pair<int, int>> q2;
    q2.push({0, 0});
    vis[0][0] = 2;
    while (!q2.empty()) {
        auto [x, y] = q2.front();
        q2.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx > 2 * n || ny < 0 || ny > 2 * m) {
                continue;
            }
            if (vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = 2;
            q2.push({nx, ny});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[2 * i + 1][2 * j + 1]) {
                ans++;
            }
        }
    }

    cout << ans << endl;
}
