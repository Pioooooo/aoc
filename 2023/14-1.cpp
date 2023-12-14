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
    int n = dat.size(), m = dat[0].size();
    for (int i = 0; i < m; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) {
            switch (dat[j][i]) {
                case '#':
                    cur = j + 1;
                    break;
                case 'O':
                    sum += n - (cur++);
                    break;
            }
        }
    }
    cout << sum << endl;
}
