#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}, x, y;

bool valid(int i, int j) { return 0 <= i && i < x && 0 <= j && j < y; }

int main() {
    ifstream fin("in");
    string line;
    int sx, sy, ex, ey;
    vector<string> dat;
    vector<vector<bool>> v;
    while (fin >> line) {
        auto s = line.find('S'), e = line.find('E');
        if (s != string::npos) {
            sy = dat.size();
            sx = s;
            line[s] = 'a';
        }
        if (e != string::npos) {
            ey = dat.size();
            ex = e;
            line[e] = 'z';
        }
        dat.push_back(line);
        vector<bool> r(line.size(), false);
        v.push_back(r);
    }
    y = dat.size();
    x = dat[0].size();
    queue<tuple<int, int, int>> q;
    q.push({ex, ey, 0});
    v[ey][ex] = 1;
    while (!q.empty()) {
        auto [i, j, d] = q.front();
        q.pop();
        for (size_t k = 0; k < 4; k++) {
            auto ii = i + dx[k], jj = j + dy[k];
            if (valid(ii, jj) && !v[jj][ii] && dat[jj][ii] + 1 >= dat[j][i]) {
                if (dat[jj][ii] == 'a') {
                    cout << d + 1 << endl;
                    exit(0);
                }
                v[jj][ii] = 1;
                q.push({ii, jj, d + 1});
            }
        }
    }
}