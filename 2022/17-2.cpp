#include <bits/stdc++.h>
using namespace std;

const int w = 7;
const long t = 1000000000000;
const int stoneCnt = 5;

vector<array<bool, w>> chamber = {};
long h = 0;

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

const int hInfo = 13;

struct towerInfo {
    array<array<bool, w>, hInfo> top;
    int iStone, iWind;
    bool operator==(const towerInfo &other) const = default;
};

namespace std {
template <>
struct hash<towerInfo> {
    size_t operator()(const towerInfo &info) const {
        size_t h = 0;
        size_t i = 0;
        for (const auto &row : info.top) {
            for (const auto &cell : row) {
                h = h ^
                    (std::hash<bool>{}(cell) << (i++ % (sizeof(size_t) * 8)));
            }
        }
        h = h ^ std::hash<int>{}(info.iStone);
        h = h ^ std::hash<int>{}(info.iWind) << 32;
        return h;
    }
};
}  // namespace std

unordered_map<towerInfo, pair<long, long>> seen;

towerInfo gatherInfo(long i) {
    towerInfo ret;
    copy_n(chamber.begin() + h - hInfo, hInfo, ret.top.begin());
    ret.iStone = indStone;
    ret.iWind = indWind;
    return ret;
}

int main() {
    ifstream fin("in");
    fin >> wind;
    long hAdditional = 0;
    bool done = false;
    for (size_t i = 0; i < t; i++) {
        const auto &st = nextStone();
        long x = 2;
        long j = h + 3;
        chamber.resize(j + 4);
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
        if (h >= hInfo && !done) {
            auto info = gatherInfo(i);
            if (seen.contains(info)) {
                auto [hLast, iLast] = seen[info];
                auto repeat = (t - i) / (i - iLast);
                hAdditional = repeat * (h - hLast);
                i += repeat * (i - iLast);
                done = true;
            }
            seen[info] = {h, i};
        }
    }
    cout << h + hAdditional << endl;
}