#include <bits/stdc++.h>
using namespace std;

vector<string> dat;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}, x, y;

bool valid(int i, int j) { return 0 <= i && i < x && 0 <= j && j < y; }

bool visible(int i, int j) {
    auto h = dat[i][j];
    for (size_t k = 0; k < 4; k++) {
        int ti = i + dx[k], tj = j + dy[k];
        while (valid(ti, tj) && dat[ti][tj] < h) {
            ti += dx[k];
            tj += dy[k];
        }
        if (!valid(ti, tj)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("in");
    string line;
    while (fin >> line) {
        dat.push_back(line);
    }
    y = dat.size(), x = dat[0].size();
    int ans = 0;
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            ans += visible(i, j);
        }
    }
    cout << ans << endl;
}