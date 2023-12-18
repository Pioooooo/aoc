#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0;
    string word;
    char c;
    int n;
    long long x = 0, y = 0;
    long long a = 0, b = 0;
    while (fin >> c >> n >> word) {
        from_chars(word.data() + 2, word.data() + 7, n, 16);
        b += n;
        long long xx = x, yy = y;
        switch (word[7]) {
            case '0':
                xx += n;
                break;
            case '1':
                yy -= n;
                break;
            case '2':
                xx -= n;
                break;
            case '3':
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
