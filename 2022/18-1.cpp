#include <bits/stdc++.h>
using namespace std;

const int N = 40;

bool lava[N][N][N] = {};

int dx[] = {0, 0, 1, -1, 0, 0},
    dy[] = {1, -1, 0, 0, 0, 0},
    dz[] = {0, 0, 0, 0, 1, -1};

bool valid(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

int main() {
    ifstream fin("in");
    int x, y, z;
    char c;
    while (fin >> x >> c >> y >> c >> z) {
        lava[x][y][z] = 1;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (lava[i][j][k]) {
                    for (size_t l = 0; l < 6; l++) {
                        int ii = i + dx[l], jj = j + dy[l], kk = k + dz[l];
                        if (valid(ii, jj, kk)) {
                            if (!lava[ii][jj][kk]) {
                                ans++;
                            }
                        } else {
                            ans++;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;
}