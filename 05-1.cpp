#include <bits/stdc++.h>
using namespace std;

int dat[1000][1000] = {0}, tot = 0;

int main() {
    ifstream fin("in");
    int x1, x2, y1, y2;
    string line;
    while (getline(fin, line)) {
        int i = line.find(','), j;
        x1 = stoi(line.substr(0, i));
        y1 = stoi(line.substr(i + 1, line.find(' ', i) - i - 1));
        x2 = stoi(
            line.substr(i = line.rfind(' ') + 1, (j = line.rfind(',')) - i));
        y2 = stoi(line.substr(j + 1));
        if (x1 != x2 && y1 != y2) {
            continue;
        }
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        for (size_t n = x1; n <= x2; n++) {
            for (size_t m = y1; m <= y2; m++) {
                if (dat[n][m] == 1) {
                    tot++;
                }
                dat[n][m]++;
            }
        }
    }
    cout << tot << endl;
}