#include <bits/stdc++.h>
using namespace std;

map<string, int> ids;

const int N = 30;
int tot = 0, s, e;
bool big[N];
bool v[N];
bool path[N][N];

void add(const string &a) {
    if (!ids.contains(a)) {
        ids[a] = tot;
        if (a.compare("start") == 0) {
            s = tot;
        }
        if (a.compare("end") == 0) {
            e = tot;
        }
        big[tot++] = isupper(a[0]);
    }
}

void add(const string &a, const string &b) {
    add(a);
    add(b);
    path[ids[a]][ids[b]] = 1;
    path[ids[b]][ids[a]] = 1;
}

int ans = 0;

void dfs(int n) {
    for (size_t i = 0; i < tot; i++) {
        if (!v[i] && path[n][i]) {
            if (i == e) {
                ans++;
                continue;
            }
            v[i] = !big[i];
            dfs(i);
            v[i] = false;
        }
    }
}

int main() {
    ifstream fin("in");
    string line;
    while (fin >> line) {
        int dash = line.find('-');
        add(line.substr(0, dash), line.substr(dash + 1));
    }
    v[s] = 1;
    dfs(s);
    cout << ans << endl;
}