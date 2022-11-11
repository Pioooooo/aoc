#include <bits/stdc++.h>
using namespace std;

int dat[100][100], dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}, x, y = 0;

bool between(int l, int r, int x) { return l <= x && x < r; }

bool check(int i, int j) {
    for (size_t k = 0; k < 4; k++) {
        if (between(0, y, j + dy[k]) && between(0, x, i + dx[k]) &&
            dat[j][i] >= dat[j + dy[k]][i + dx[k]]) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("in");
    string line;
    while (getline(fin, line)) {
        x = line.length() - 1;
        for (size_t i = 0; i < x; i++) {
            dat[y][i] = line[i] - '0';
        }
        y++;
    }
    int tot = 0;
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            if (check(i, j)) {
                tot += dat[j][i] + 1;
            }
        }
    }
    cout << tot << endl;
}