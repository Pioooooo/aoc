#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> dat;
    while (getline(fin, line)) {
        dat.push_back(line);
    }
    int n = dat.size(), m = dat[0].size();
    vector dis(n, vector(m, array<int, 4>{-1, -1, -1, -1}));
    queue<tuple<int, int, int>> q;
    q.emplace(0, 0, 0);
    q.emplace(0, 0, 1);
    dis[0][0] = {0, 0, 0, 0};
    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();

        for (int dd = (d & 1) ^ 1; dd < 4; dd += 2) {
            auto dist = dis[y][x][d];
            for (int l = 1; l < 4; l++) {
                auto xx = x + l * dx[dd], yy = y + l * dy[dd];
                if (xx < 0 || xx >= m || yy < 0 || yy >= n) {
                    break;
                }
                dist += dat[yy][xx] - '0';
                if (dist < dis[yy][xx][dd] || dis[yy][xx][dd] == -1) {
                    dis[yy][xx][dd] = dist;
                    q.emplace(xx, yy, dd);
                }
            }
        }
    }
    cout << ranges::min(dis.back().back() |
                        views::filter([](int i) { return i >= 0; }))
         << endl;
}
