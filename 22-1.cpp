#include <bits/stdc++.h>
using namespace std;

bool cubes[101][101][101] = {};

int main() {
    ifstream fin("in");
    string word;
    char c;
    while (fin >> word >> c >> c) {
        int s[3], t[3];
        fin >> s[0];
        fin.ignore(2) >> t[0];
        fin.ignore(3) >> s[1];
        fin.ignore(2) >> t[1];
        fin.ignore(3) >> s[2];
        fin.ignore(2) >> t[2];
        auto valid = [](const int& i) { return abs(i) > 50; };
        if (any_of(s, s + 3, valid) || any_of(t, t + 3, valid)) {
            continue;
        }
        bool on = word.size() == 2;
        for (int x = s[0]; x <= t[0]; x++) {
            for (int y = s[1]; y <= t[1]; y++) {
                for (int z = s[2]; z <= t[2]; z++) {
                    cubes[x + 50][y + 50][z + 50] = on;
                }
            }
        }
    }

    int ans = 0;
    for (size_t x = 0; x <= 100; x++) {
        for (size_t y = 0; y <= 100; y++) {
            for (size_t z = 0; z <= 100; z++) {
                ans += cubes[x][y][z];
            }
        }
    }
    cout << ans << endl;
}