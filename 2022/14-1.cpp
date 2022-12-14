#include <bits/stdc++.h>
using namespace std;

const int X = 600, Y = 200;

int dat[X][Y] = {};

void modify(int &i, int &j, const int &x, const int &y) {
    if (x > i)
        i++;
    else if (x < i)
        i--;
    else if (y > j)
        j++;
    else if (y < j)
        j--;
}

bool valid(int x, int y) { return 0 <= x && x < X && 0 <= y && y <= Y; }

int main() {
    ifstream fin("in");
    string line, word;
    int x, y;
    char c;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> x >> c >> y;
        int x1, y1;
        while (ss >> word >> x1 >> c >> y1) {
            for (int i = x, j = y; i != x1 || j != y1; modify(i, j, x1, y1)) {
                dat[i][j] = 1;
            }
            x = x1;
            y = y1;
        }
        dat[x][y] = 1;
    }
    int ans = 0;
    while (true) {
        x = 500, y = 0;
        while (true) {
            while (valid(x, y + 1) && !dat[x][y + 1]) {
                y++;
            }
            if (y == Y) {
                cout << ans << endl;
                exit(0);
            }
            if (!dat[x - 1][y + 1]) {
                x--;
                y++;
            } else if (!dat[x + 1][y + 1]) {
                x++;
                y++;
            } else {
                dat[x][y] = 1;
                ans++;
                break;
            }
        }
    }
}