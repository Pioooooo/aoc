#include <bits/stdc++.h>
using namespace std;

const int N = 40;

bool lava[N][N][N] = {};
bool visited[N][N][N] = {};

int dx[] = {0, 0, 1, -1, 0, 0}, dy[] = {1, -1, 0, 0, 0, 0},
    dz[] = {0, 0, 0, 0, 1, -1};

bool valid(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

int main() {
    ifstream fin("in");
    int x, y, z;
    char c;
    while (fin >> x >> c >> y >> c >> z) {
        lava[x + 1][y + 1][z + 1] = 1;
    }
    int ans = 0;
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    visited[0][0][0] = true;
    while (!q.empty()) {
        auto [i, j, k] = q.front();
        q.pop();
        for (size_t l = 0; l < 6; l++) {
            int ii = i + dx[l], jj = j + dy[l], kk = k + dz[l];
            if (valid(ii, jj, kk)) {
                if (lava[ii][jj][kk]) {
                    ans++;
                } else if (!visited[ii][jj][kk]) {
                    q.push({ii, jj, kk});
                    visited[ii][jj][kk] = true;
                }
            }
        }
    }
    cout << ans << endl;
}