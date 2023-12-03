#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> engine;
    while (getline(fin, line)) {
        engine.push_back(line);
    }
    int n = engine.size(), m = engine[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isdigit(engine[i][j])) {
                continue;
            }
            int cur = engine[i][j] - '0', l = 0;
            while (j + (++l) < m) {
                if (!isdigit(engine[i][j + l])) {
                    break;
                }
                cur = cur * 10 + engine[i][j + l] - '0';
            }
            bool found = false;
            if (i > 0) {
                for (int k = max(0, j - 1); k < min(m, j + l + 1); k++) {
                    if (!isdigit(engine[i - 1][k]) && engine[i - 1][k] != '.') {
                        found = true;
                        break;
                    }
                }
            }
            if (!found && i + 1 < n) {
                for (int k = max(0, j - 1); k < min(m, j + l + 1); k++) {
                    if (!isdigit(engine[i + 1][k]) && engine[i + 1][k] != '.') {
                        found = true;
                        break;
                    }
                }
            }
            if (!found && j > 0 && !isdigit(engine[i][j - 1]) &&
                engine[i][j - 1] != '.') {
                found = true;
            }
            if (!found && j + l < m && !isdigit(engine[i][j + l]) &&
                engine[i][j + l] != '.') {
                found = true;
            }
            if (found) {
                sum += cur;
            }
            j += l;
        }
    }
    cout << sum << endl;
}