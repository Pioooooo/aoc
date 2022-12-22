#include <bits/stdc++.h>
using namespace std;

vector<string> dat;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool valid(int x, int y) {
    return 0 <= y && y < dat.size() && 0 <= x && x < dat[y].size() &&
           dat[y][x] != ' ';
}

int main() {
    ifstream fin("in");
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            break;
        }
        dat.push_back(line);
    }

    int x = dat[0].find('.'), y = 0, k = 0;
    int l;
    char c;
    while (fin >> l) {
        while (l--) {
            int xx = x + dx[k], yy = y + dy[k];
            if (!valid(xx, yy)) {
                xx = x;
                yy = y;
                while (valid(xx - dx[k], yy - dy[k])) {
                    xx -= dx[k];
                    yy -= dy[k];
                }
            }
            if (dat[yy][xx] == '#') {
                break;
            }
            x = xx;
            y = yy;
        }
        cout << '(' << y << ", " << x << ')' << ' ' << k << endl;
        if (!(fin >> c)) {
            break;
        }
        if (c == 'L') {
            k = (k + 3) % 4;
        } else {
            k = (k + 1) % 4;
        }
    }
    cout << 1000 * (y + 1) + 4 * (x + 1) + k << endl;
}