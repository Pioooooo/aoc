#include <bits/stdc++.h>
using namespace std;

int dice = -3, cnt = 0;

int next() {
    cnt++;
    return dice += 9;
}

int main() {
    ifstream fin("in");
    string word;
    int a, b;
    fin >> word >> word >> word >> word >> a;
    fin >> word >> word >> word >> word >> b;
    a--;
    b--;
    int sa = 0, sb = 0;
    while (sa < 1000 && sb < 1000) {
        a += next();
        a %= 10;
        sa += a + 1;
        if (sa >= 1000) {
            cout << sb * 3 * cnt << endl;
            break;
        }
        b += next();
        b %= 10;
        sb += b + 1;
        if (sb >= 1000) {
            cout << sa * 3 * cnt << endl;
        }
    }
}