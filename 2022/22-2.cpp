#include <bits/stdc++.h>
using namespace std;

vector<string> dat;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool valid(int x, int y) {
    return 0 <= y && y < dat.size() && 0 <= x && x < dat[y].size() &&
           dat[y][x] != ' ';
}

const int w = 50;

int side(int x, int y) {
    x /= w;
    y /= w;
    if (make_pair(x, y) == make_pair(1, 0)) {
        return 0;
    }
    if (make_pair(x, y) == make_pair(1, 1)) {
        return 1;
    }
    if (make_pair(x, y) == make_pair(1, 2)) {
        return 2;
    }
    if (make_pair(x, y) == make_pair(0, 2)) {
        return 3;
    }
    if (make_pair(x, y) == make_pair(0, 3)) {
        return 4;
    }
    if (make_pair(x, y) == make_pair(2, 0)) {
        return 5;
    }
}

tuple<int, int, int> nxt(int x, int y, int k) {
    int s = side(x, y), xx = x += dx[k], yy = y += dy[k];
    if (!valid(x, y)) {
        switch (s) {
            case 0:  // f
                x -= w;
                switch (k) {
                    case 0:  // r
                        break;
                    case 1:  // d
                        break;
                    case 2:  // l
                        xx = 0;
                        yy = w * 3 - y - 1;
                        k = 0;
                        break;
                    case 3:  // u
                        xx = 0;
                        yy = x + w * 3;
                        k = 0;
                        break;
                    default:
                        throw -1;
                }
                break;
            case 1:  // d
                x -= w;
                y -= w;
                switch (k) {
                    case 0:  // r
                        xx = w * 2 + y;
                        yy = w - 1;
                        k = 3;
                        break;
                    case 1:  // b
                        break;
                    case 2:  // l
                        xx = y;
                        yy = w * 2;
                        k = 1;
                        break;
                    case 3:  // f
                        break;
                    default:
                        throw -1;
                }
                break;
            case 2:  // b
                x -= w;
                y -= w * 2;
                switch (k) {
                    case 0:  // r
                        xx = w * 3 - 1;
                        yy = w - y - 1;
                        k = 2;
                        break;
                    case 1:  // u
                        xx = w - 1;
                        yy = w * 3 + x;
                        k = 2;
                        break;
                    case 2:  // l
                        break;
                    case 3:  // d
                        break;
                    default:
                        throw -1;
                }
                break;
            case 3:  // l
                y -= w * 2;
                switch (k) {
                    case 0:  // b
                        break;
                    case 1:  // u
                        break;
                    case 2:  // f
                        xx = w;
                        yy = w - y - 1;
                        k = 0;
                        break;
                    case 3:  // d
                        xx = w;
                        yy = w + x;
                        k = 0;
                        break;
                    default:
                        throw -1;
                }
                break;
            case 4:  // u
                y -= w * 3;
                switch (k) {
                    case 0:  // b
                        xx = w + y;
                        yy = w * 3 - 1;
                        k = 3;
                        break;
                    case 1:  // r
                        xx = w * 2 + x;
                        yy = 0;
                        break;
                    case 2:  // f
                        xx = w + y;
                        yy = 0;
                        k = 1;
                        break;
                    case 3:  // l
                        break;
                    default:
                        throw -1;
                }
                break;
            case 5:  // r
                x -= w * 2;
                switch (k) {
                    case 0:  // b
                        xx = w * 2 - 1;
                        yy = w * 3 - y - 1;
                        k = 2;
                        break;
                    case 1:  // d
                        xx = w * 2 - 1;
                        yy = w + x;
                        k = 2;
                        break;
                    case 2:  // f
                        break;
                    case 3:  // u
                        xx = x;
                        yy = w * 4 - 1;
                        break;
                    default:
                        throw -1;
                }
                break;
            default:
                throw -1;
        }
    }
    if (!valid(xx, yy)) {
        throw -1;
    }
    return {xx, yy, k};
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

    int x = dat[0].find('.'), y = 0, k = 0, s = 0;
    int l;
    char c;
    while (fin >> l) {
        while (l--) {
            auto [xx, yy, kk] = nxt(x, y, k);
            if (dat[yy][xx] == '#') {
                break;
            }
            x = xx;
            y = yy;
            k = kk;
        }
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