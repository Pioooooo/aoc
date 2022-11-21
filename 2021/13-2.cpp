#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    freopen("out", "w", stdout);
    vector<pair<int, int>> dots;
    string line;
    while (getline(fin, line)) {
        auto deli = line.find(',');
        if (deli == string::npos) {
            break;
        }
        int x = stoi(line.substr(0, deli)), y = stoi(line.substr(deli + 1));
        dots.push_back({x, y});
    }
    int minx = 1e4, miny = 1e4;
    while (fin >> line >> line >> line) {
        int num;
        switch (line[0]) {
            case 'x':
                num = stoi(line.substr(2));
                minx = min(minx, num);
                for_each(dots.begin(), dots.end(), [&](auto &dot) {
                    if (dot.first > num) {
                        dot.first = 2 * num - dot.first;
                    }
                });
                break;
            case 'y':
                num = stoi(line.substr(2));
                miny = min(miny, num);
                for_each(dots.begin(), dots.end(), [&](auto &dot) {
                    if (dot.second > num) {
                        dot.second = 2 * num - dot.second;
                    }
                });
                break;
            default:
                throw -1;
                break;
        }
    }
    set<decltype(dots)::value_type> cnt(dots.begin(), dots.end());
    for (size_t i = 0; i < minx; i++) {
        for (size_t j = 0; j < miny; j++) {
            cout << (cnt.contains({i, j}) ? '#' : ' ');
        }
        cout << endl;
    }
}