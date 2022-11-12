#include <bits/stdc++.h>
using namespace std;

bool test(int vx, int vy, int x0, int x1, int y0, int y1) {
    int x = 0, y = 0;
    while (x <= x1 && y >= y0) {
        x += vx;
        y += vy;
        vx--;
        vx = max(0, vx);
        vy--;
        if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
            return true;
        }
    }
    return false;
}

int main() {
    int x0, x1, y0, y1;
    ifstream fin("in");
    string word;
    fin >> word >> word;
    (fin.ignore(3) >> x0).ignore(2) >> x1;
    (fin.ignore(4) >> y0).ignore(2) >> y1;
    int maxvx = x1, minvx = sqrt(x0);
    while (minvx * (minvx + 1) / 2 < x0) {
        minvx++;
    }

    int maxvy = -y0 - 1, minvy = y0, tot = 0;
    for (int vx = minvx; vx <= maxvx; vx++) {
        for (int vy = minvy; vy <= maxvy; vy++) {
            tot += test(vx, vy, x0, x1, y0, y1);
        }
    }
    cout << tot << endl;
}