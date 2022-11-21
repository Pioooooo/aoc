#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line;
    vector<string> dat;
    while (fin >> line) {
        dat.push_back(line);
    }
    int x = dat[0].size(), y = dat.size();
    int ans = 0;
    while (true) {
        ans++;
        bool moved = false;
        queue<pair<size_t, size_t>> movable;
        for (size_t i = 0; i < x; i++) {
            for (size_t j = 0; j < y; j++) {
                if (dat[j][i] == '>' && dat[j][(i + 1) % x] == '.') {
                    movable.push({j, i});
                }
            }
        }
        while (!movable.empty()) {
            auto [j, i] = movable.front();
            movable.pop();
            swap(dat[j][i], dat[j][(i + 1) % x]);
            moved = true;
        }

        for (size_t i = 0; i < x; i++) {
            for (size_t j = 0; j < y; j++) {
                if (dat[j][i] == 'v' && dat[(j + 1) % y][i] == '.') {
                    movable.push({j, i});
                }
            }
        }
        while (!movable.empty()) {
            auto [j, i] = movable.front();
            movable.pop();
            swap(dat[j][i], dat[(j + 1) % y][i]);
            moved = true;
        }
        if (!moved) {
            break;
        }
    }
    cout << ans << endl;
}