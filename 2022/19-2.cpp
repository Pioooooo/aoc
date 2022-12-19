#include <bits/stdc++.h>
using namespace std;

const int t = 32;

struct TupleHash {
    template <typename T>
    std::size_t operator()(const T &t) const {
        std::size_t seed = 0;
        seed ^= std::hash<int>()(std::get<0>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<1>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<2>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<3>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<4>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<5>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        seed ^= std::hash<int>()(std::get<6>(t)) + 0x9e3779b9 + (seed << 6) +
                (seed >> 2);
        return seed;
    }
};

int main() {
    ifstream fin("in");
    string word;
    int ore, clay, obsi[2], geode[2], i = 0;
    vector<int> ans;
    ans.resize(3, 1);
    while (fin >> word >> word >> word >> word >> word >> word >> ore >> word >>
           word >> word >> word >> word >> clay >> word >> word >> word >>
           word >> word >> obsi[0] >> word >> word >> obsi[1] >> word >> word >>
           word >> word >> word >> geode[0] >> word >> word >> geode[1] >>
           word) {
        i++;
        if (i > 3) {
            break;
        }
        //  ore, clay, obsi, geode<robot, resource>
        int maxore = max({ore, clay, obsi[0], geode[0]});
        unordered_map<tuple<int, int, int, int, int, int, int>, int, TupleHash>
            dp[t + 1];
        dp[0][{1, 0, 0, 0, 0, 0, 0}] = 0;
        for (int i = 0; i < t; i++) {
            for (auto &&[k, ngeode] : dp[i]) {
                auto [rore, rclay, robsi, rgeode, nore, nclay, nobsi] = k;
                rore = min(rore, maxore);
                rclay = min(rclay, obsi[1]);
                robsi = min(robsi, geode[1]);
                nore = min(nore, (t - i) * maxore - (t - 1 - i) * rore);
                nclay = min(nclay, (t - i) * obsi[1] - (t - 1 - i) * rclay);
                nobsi = min(nobsi, (t - i) * geode[1] - (t - 1 - i) * robsi);
                if (nore >= geode[0] && nobsi >= geode[1]) {
                    dp[i + 1]
                      [{rore, rclay, robsi, rgeode + 1, nore - geode[0] + rore,
                        nclay + rclay, nobsi - geode[1] + robsi}] =
                          max(ngeode + rgeode,
                              dp[i + 1][{rore, rclay, robsi, rgeode + 1,
                                         nore - geode[0] + rore, nclay + rclay,
                                         nobsi - geode[1] + robsi}]);
                    continue;
                }
                if (nore >= ore) {
                    dp[i + 1]
                      [{rore + 1, rclay, robsi, rgeode, nore - ore + rore,
                        nclay + rclay, nobsi + robsi}] =
                          max(ngeode + rgeode,
                              dp[i + 1][{rore + 1, rclay, robsi, rgeode,
                                         nore - ore + rore, nclay + rclay,
                                         nobsi + robsi}]);
                }
                if (nore >= clay) {
                    dp[i + 1]
                      [{rore, rclay + 1, robsi, rgeode, nore - clay + rore,
                        nclay + rclay, nobsi + robsi}] =
                          max(ngeode + rgeode,
                              dp[i + 1][{rore, rclay + 1, robsi, rgeode,
                                         nore - clay + rore, nclay + rclay,
                                         nobsi + robsi}]);
                }
                if (nore >= obsi[0] && nclay >= obsi[1]) {
                    dp[i + 1]
                      [{rore, rclay, robsi + 1, rgeode, nore - obsi[0] + rore,
                        nclay - obsi[1] + rclay, nobsi + robsi}] =
                          max(ngeode + rgeode,
                              dp[i + 1]
                                [{rore, rclay, robsi + 1, rgeode,
                                  nore - obsi[0] + rore,
                                  nclay - obsi[1] + rclay, nobsi + robsi}]);
                }
                dp[i + 1][{rore, rclay, robsi, rgeode, nore + rore,
                           nclay + rclay, nobsi + robsi}] =
                    max(ngeode + rgeode,
                        dp[i + 1][{rore, rclay, robsi, rgeode, nore + rore,
                                   nclay + rclay, nobsi + robsi}]);
            }
        }
        int tmp = 0;
        for (auto &&[k, v] : dp[t]) {
            tmp = max(tmp, v);
        }
        ans[i - 1] = tmp;
    }
    cout << accumulate(ans.begin(), ans.begin() + 3, 1, multiplies<int>{})
         << endl;
}