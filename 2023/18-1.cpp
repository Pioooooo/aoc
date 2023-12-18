#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string word;
    char c;
    int n;
    int x = 0, y = 0;
    int a = 0, b = 0;
    while (fin >> c >> n >> word) {
        b += n;
        int xx = x, yy = y;
        switch (c) {
            case 'R':
                xx += n;
                break;
            case 'D':
                yy -= n;
                break;
            case 'L':
                xx -= n;
                break;
            case 'U':
                yy += n;
                break;
            default:
                unreachable();
        }
        a += yy * x - xx * y;
        x = xx, y = yy;
    }
    assert(x == 0 && y == 0);
    cout << abs(a) / 2 + b / 2 + 1 << endl;
}
