#include <bits/stdc++.h>
using namespace std;

const int w = 7;
const int t = 2022;
const int stoneCnt = 5;

bool chamber[t * 4][w] = {};
int h = 0;

typedef vector<pair<int, int>> stone;

stone stones[] = {{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                  {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
                  {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}},
                  {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                  {{0, 0}, {0, 1}, {1, 0}, {1, 1}}};
int indStone = 0;

const stone &nextStone() {
    auto &ret = stones[indStone];
    indStone = (indStone + 1) % stoneCnt;
    return ret;
}

string wind;
int indWind = 0;

bool nextWind() {
    auto ret = wind[indWind] == '<';
    indWind = (indWind + 1) % wind.size();
    return ret;
}

int main() {
    ifstream fin("in");
    fin >> wind;
    for (size_t i = 0; i < t; i++) {
        const auto &st = nextStone();
        int x = 2;
        int j = h + 3;
        while (true) {
            auto wd = nextWind();
            bool ok = true;
            if (wd) {
                for (auto &&[y, xOff] : st) {
                    if (x + xOff == 0 || chamber[j + y][x + xOff - 1]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    x--;
                }
            } else {
                for (auto &&[y, xOff] : st) {
                    if (x + xOff + 1 == w || chamber[j + y][x + xOff + 1]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    x++;
                }
            }
            ok = false;
            if (j != 0) {
                ok = true;
                for (auto &&[y, xOff] : st) {
                    if (chamber[j + y - 1][x + xOff]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) {
                for (auto &&[y, xOff] : st) {
                    chamber[j + y][x + xOff] = true;
                    h = max(h, j + y + 1);
                }
                break;
            }
            j--;
        }
        cout << h << endl;
    }
    cout << h << endl;
}