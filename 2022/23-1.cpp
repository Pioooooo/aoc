#include <bits/stdc++.h>
using namespace std;

const int t = 10;

typedef pair<int, int> pos;

set<pos> elves;

int dx[] = {0, 0, -1, 1, 1, 1, -1, -1}, dy[] = {-1, 1, 0, 0, 1, -1, 1, -1};

bool adjClr(pos p) {
    auto &[x, y] = p;
    for (size_t i = 0; i < 8; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (elves.contains({xx, yy})) {
            return false;
        }
    }
    return true;
}

void print() {
    return;
    const int n = 15;
    for (int i = -t; i < n; i++) {
        for (int j = -t; j < n; j++) {
            cout << (elves.contains({j, i}) ? '#' : '.');
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ifstream fin("in");
    int y = 0;
    string line;
    while (fin >> line) {
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '#') {
                elves.insert({i, y});
            }
        }
        y++;
    }
    print();
    for (size_t i = 0; i < t; i++) {
        multimap<pos, pos> old;
        for (auto &&[x, y] : elves) {
            if (adjClr({x, y})) {
                old.insert({{x, y}, {x, y}});
                continue;
            }
            bool fl = false;
            for (size_t j = 0; j < 4; j++) {
                int jj = (j + i) % 4;
                int xx = x + dx[jj], yy = y + dy[jj];
                if (!elves.contains({xx, yy}) &&
                    !elves.contains(
                        {xx + dx[(jj + 2) % 4], yy + dy[(jj + 2) % 4]}) &&
                    !elves.contains(
                        {xx - dx[(jj + 2) % 4], yy - dy[(jj + 2) % 4]})) {
                    old.insert({{xx, yy}, {x, y}});
                    fl = true;
                    break;
                }
            }
            if (!fl) {
                old.insert({{x, y}, {x, y}});
            }
        }
        elves.clear();
        for (auto it = old.begin(); it != old.end();
             it = old.upper_bound(it->first)) {
            int cnt = old.count(it->first);
            if (cnt > 1) {
                auto [bg, ed] = old.equal_range(it->first);
                for (auto jt = bg; jt != ed; jt++) {
                    elves.insert(jt->second);
                }
            } else {
                elves.insert(it->first);
            }
        }
        print();
    }
    auto [minx, miny] = *elves.begin();
    auto [maxx, maxy] = *elves.begin();
    for (auto &&[x, y] : elves) {
        minx = min(minx, x);
        miny = min(miny, y);
        maxx = max(maxx, x);
        maxy = max(maxy, y);
    }
    cout << (maxx - minx + 1) * (maxy - miny + 1) - elves.size() << endl;
}