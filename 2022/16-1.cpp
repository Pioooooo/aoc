#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int n = 0;
map<string, int> nodes;
string rnodes[N];

bool dat[N][N] = {};
int rate[N] = {};
int hasRate[N] = {}, tot = 0;

void init(const string &s) {
    if (!nodes.contains(s)) {
        rnodes[n] = s;
        nodes[s] = n++;
    }
}

void add(const string &a, const string &b) {
    init(a);
    init(b);
    dat[nodes[a]][nodes[b]] = 1;
}

int dis[N][N] = {};

void bfs() {
    for (int i = 0; i < n; i++) {
        int v[N] = {};
        queue<pair<int, int>> q;
        q.push({i, 0});
        v[i] = 1;
        while (!q.empty()) {
            auto &[c, d] = q.front();
            q.pop();
            for (int j = 0; j < n; j++) {
                if (dat[c][j] && !v[j]) {
                    if (rate[j]) {
                        dis[i][j] = d + 1;
                    }
                    v[j] = 1;
                    q.push({j, d + 1});
                }
            }
        }
    }
}

typedef long long stat;

int rel(stat s) {
    int ret = 0;
    for (int i = 0; i < tot; i++) {
        if (s & 1) {
            ret += rate[hasRate[i]];
        }
        s >>= 1;
    }
    return ret;
}

int main() {
    ifstream fin("in");
    string line, word, name, name1;
    char c;
    int r;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> word >> name >> word >> word;
        ss >> c >> c >> c >> c >> c >> r >> c;
        ss >> word >> word >> word >> word;
        while (ss >> name1) {
            name1 = name1.substr(0, name1.find(','));
            add(name, name1);
        }
        rate[nodes[name]] = r;
        if (r) {
            hasRate[tot++] = nodes[name];
        }
    }
    bfs();

    int s = nodes["AA"];
    map<int, map<pair<int, long long>, int>> dp;
    dp[0] = {{{s, 0}, 0}};
    for (size_t i = 0; i < 30; i++) {
        auto cur = dp[i];
        for (auto &&[tup, score] : cur) {
            dp[i + 1][{tup}] = max(dp[i + 1][{tup}], score + rel(tup.second));
            for (size_t j = 0; j < tot; j++) {
                auto [pos, visited] = tup;
                if (!(visited & 1 << j)) {
                    visited |= 1 << j;
                    dp[i + dis[pos][hasRate[j]] + 1][{hasRate[j], visited}] =
                        max(dp[i + dis[pos][hasRate[j]] + 1]
                              [{hasRate[j], visited}],
                            score +
                                rel(tup.second) * (dis[pos][hasRate[j]] + 1));
                }
            }
        }
    }
    int ans = 0;
    for (auto &&[k, score] : dp[30]) {
        ans = max(ans, score);
    }
    cout << ans << endl;
}