#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
map<char, pair<int, int>> dir = {
    {'|', {0, 1}}, {'-', {2, 3}}, {'L', {1, 2}},
    {'J', {1, 3}}, {'7', {0, 3}}, {'F', {0, 2}},
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
            if (distance[nx][ny] != -1) {
                ans = max(ans, distance[nx][ny]);
            } else {
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

    cout << ans << endl;
}
