#include <bits/stdc++.h>
using namespace std;

int dat[100][100], dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}, x, y = 0;
int dis[500][500];

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
    for (size_t i = 0; i < 5 * x; i++) {
        for (size_t j = 0; j < 5 * y; j++) {
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
            if (a < 0 || 5 * x <= a || b < 0 || 5 * y <= b) {
                continue;
            }
            if (dis[a][b] > dis[p.first][p.second] +
                                (dat[a % x][b % y] + a / x + b / y - 1) % 9 +
                                1) {
                dis[a][b] = dis[p.first][p.second] +
                            (dat[a % x][b % y] + a / x + b / y - 1) % 9 + 1;
                q.push({a, b});
            }
        }
    }
    cout << dis[5 * x - 1][5 * y - 1] << endl;
}