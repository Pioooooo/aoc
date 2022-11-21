#include <bits/stdc++.h>
using namespace std;

int dat[10][10], dx[8] = {1, 1, 1, 0, -1, -1, -1, 0},
                 dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};

bool between(int x) { return 0 <= x && x < 10; }

int main() {
    ifstream fin("in");
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            char c;
            fin >> c;
            dat[i][j] = c - '0';
        }
    }
    int n = 100, tot = 0;
    while (n--) {
        queue<pair<int, int>> q;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < 10; j++) {
                if (dat[i][j] > 9) {
                    dat[i][j] = 0;
                }
                if (++dat[i][j] > 9) {
                    tot++;
                    q.push({i, j});
                }
            }
        }
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            for (size_t i = 0; i < 8; i++) {
                int a = p.first + dx[i], b = p.second + dy[i];
                if (between(a) && between(b)) {
                    dat[a][b]++;
                    if (dat[a][b] == 10) {
                        tot++;
                        q.push({a, b});
                    }
                }
            }
        }
    }
    cout << tot << endl;
}