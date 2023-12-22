#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main() {
    ifstream fin("in");
    long long sum = 0;
    string line;
    vector<string> dat;
    queue<pair<int, int>> q;
    pair<int, int> s;
    while (getline(fin, line)) {
        dat.push_back(line);
        auto it = line.find('S');
        if (it != string::npos) {
            s = {dat.size() - 1, it};
        }
    }
    int n = dat.size(), m = dat[0].size();
    assert(n == m);
    vector<vector<int>> vis(n * 3, vector<int>(n * 3, -1));
    q.emplace(s.first + n, s.second + n);
    vis[q.front().first][q.front().second] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < 3 * n && ny >= 0 && ny < 3 * n &&
                dat[nx % n][ny % n] != '#' && vis[nx][ny] == -1) {
                vis[nx][ny] = vis[x][y] + 1;
                q.emplace(nx, ny);
            }
        }
    }
    int steps = 26501365;
    vector<long long> dp(steps + n * 3);
    for (int i = steps; i >= 0; i--) {
        dp[i] = !((steps - i) % 2) + 2 * dp[i + n] - dp[i + 2 * n];
    }
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (vis[i + s.first][j + s.second] != -1) {
                sum += dp[vis[i + s.first][j + s.second]];
            }
        }
    }
    cout << sum << endl;
}
