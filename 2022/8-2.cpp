#include <bits/stdc++.h>
using namespace std;

vector<string> dat;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}, x, y;

bool valid(int i, int j) { return 0 <= i && i < x && 0 <= j && j < y; }

int visible(int i, int j) {
    auto h = dat[i][j];
    int ans = 1;
    for (size_t k = 0; k < 4; k++) {
        int ti = i, tj = j, cnt = 0;
        do {
            ti += dx[k];
            tj += dy[k];
            if (!valid(ti, tj)) break;
            cnt++;
        } while (dat[ti][tj] < h);
        ans *= cnt;
    }
    return ans;
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
            ans = max(ans, visible(i, j));
        }
    }
    cout << ans << endl;
}