#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0;
    string line, word;
    char c;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> word;
        auto s = word | views::transform([](char c) {
                     switch (c) {
                         case '.':
                             return 1;
                         case '#':
                             return 2;
                         case '?':
                             return 3;
                         default:
                             unreachable();
                     }
                 });
        int n, m;
        vector<int> v;
        while (ss >> n >> c) {
            v.push_back(n);
        }
        v.push_back(n);
        n = s.size(), m = v.size();
        auto checkr = [&](int i, int j, bool k) {
            for (int l = i; l < i + j; l++) {
                if (!(s[l] & (1 << k))) {
                    return false;
                }
            }
            return true;
        };

        map<pair<int, int>, long long> memo;
        function<long long(int, int)> dfs = [&](int i, int j) -> long long {
            if (memo.contains({i, j})) {
                return memo[{i, j}];
            }
            if (n - i <
                ranges::fold_left(v | views::drop(j), m - j - 1, plus<>{})) {
                return memo[{i, j}] = 0;
            }
            int g = v[j];
            long long ret = 0;
            if (j == m) {
                if (checkr(i, n - i, false)) {
                    return memo[{i, j}] = 1;
                } else {
                    return memo[{i, j}] = 0;
                }
            }
            if (i + g == n || s[i + g] & 1) {
                if (checkr(i, g, true)) {
                    ret += dfs(i + g + 1, j + 1);
                }
            }
            if (s[i] & 1) {
                ret += dfs(i + 1, j);
            }
            return memo[{i, j}] = ret;
        };
        sum += dfs(0, 0);
    }
    cout << sum << endl;
}
