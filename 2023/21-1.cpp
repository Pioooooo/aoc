#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> dat;
    queue<pair<int, int>> q;
    while (getline(fin, line)) {
        dat.push_back(line);
        auto it = line.find('S');
        if (it != string::npos) {
            q.emplace(dat.size() - 1, it);
        }
    }
    int n = dat.size(), m = dat[0].size();
    vector<vector<int>> vis(n, vector<int>(m, -1));
    vis[q.front().first][q.front().second] = 0;
    sum++;
    int step = 64;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (vis[x][y] >= step) {
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dat[nx][ny] != '#' &&
                vis[nx][ny] == -1) {
                vis[nx][ny] = vis[x][y] + 1;
                q.emplace(nx, ny);
                if ((step - vis[nx][ny]) % 2 == 0) {
                    sum++;
                }
            }
        }
    }

    cout << sum << endl;
}
