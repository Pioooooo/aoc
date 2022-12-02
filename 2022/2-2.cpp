#include <bits/stdc++.h>
using namespace std;

int score(int l, int r) {
    if ((l + 1) % 3 == r) {
        return r + 1 + 6;
    }
    if ((r + 1) % 3 == l) {
        return r + 1 + 0;
    }
    return r + 1 + 3;
}

int main() {
    ifstream fin("in");
    int dat[3][3] = {};
    char a, b;
    int ans = 0;
    while (fin >> a >> b) {
        int l = a - 'A', r = b - 'X';
        ans += score(l, (l + r + 2) % 3);
    }
    cout << ans << endl;
}