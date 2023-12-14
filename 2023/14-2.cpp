#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<string> dat;
    while (getline(fin, line)) {
        dat.push_back(line);
    }
    int r = 1000000000;
    int n = dat.size(), m = dat[0].size();

    map<string, int> history;
    map<int, string> rev;
    while (r--) {
        for (int i = 0; i < m; i++) {
            int cur = 0;
            for (int j = 0; j < n; j++) {
                switch (dat[j][i]) {
                    case '#':
                        cur = j + 1;
                        break;
                    case 'O':
                        dat[j][i] = '.';
                        dat[cur++][i] = 'O';
                        break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < m; j++) {
                switch (dat[i][j]) {
                    case '#':
                        cur = j + 1;
                        break;
                    case 'O':
                        dat[i][j] = '.';
                        dat[i][cur++] = 'O';
                        break;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int cur = n - 1;
            for (int j = n - 1; j >= 0; j--) {
                switch (dat[j][i]) {
                    case '#':
                        cur = j - 1;
                        break;
                    case 'O':
                        dat[j][i] = '.';
                        dat[cur--][i] = 'O';
                        break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int cur = m - 1;
            for (int j = m - 1; j >= 0; j--) {
                switch (dat[i][j]) {
                    case '#':
                        cur = j - 1;
                        break;
                    case 'O':
                        dat[i][j] = '.';
                        dat[i][cur--] = 'O';
                        break;
                }
            }
        }

        string tmp;
        ranges::copy(dat | views::join, back_inserter(tmp));
        if (history.contains(tmp)) {
            const string &k = rev[history[tmp] - r % (history[tmp] - r)];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (k[i * m + j] == 'O') {
                        sum += n - i;
                    }
                }
            }
            cout << sum << endl;
            return 0;
        } else {
            history[tmp] = r;
            rev[r] = tmp;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dat[i][j] == 'O') {
                sum += n - i;
            }
        }
    }
    cout << sum << endl;
}
