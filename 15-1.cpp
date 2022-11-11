#include <bits/stdc++.h>
using namespace std;

int dat[100][100], dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}, x, y = 0;
int dis[100][100];

int main() {
    ifstream fin("in");
    string line;
    while (fin >> line) {
        x = line.size();
        for (size_t i = 0; i < x; i++) {
            dat[i][y] = line[i] - '0';
        }
        y++;
    }
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            dis[i][j] = 1e9;
        }
    }
    dis[0][0] = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (size_t i = 0; i < 4; i++) {
            int a = p.first + dx[i], b = p.second + dy[i];
            if (a < 0 || x <= a || b < 0 || y <= b) {
                continue;
            }
            if (dis[a][b] > dis[p.first][p.second] + dat[a][b]) {
                dis[a][b] = dis[p.first][p.second] + dat[a][b];
                q.push({a, b});
            }
        }
    }
    cout << dis[x - 1][y - 1] << endl;
}