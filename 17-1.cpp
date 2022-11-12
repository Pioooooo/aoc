#include <bits/stdc++.h>
using namespace std;

int calc(int y) { return y > 0 ? y : -y - 1; }

int main() {
    ifstream fin("in");
    string word;
    fin >> word >> word >> word;
    int y0, y1;
    (fin.ignore(3) >> y0).ignore(2) >> y1;
    int vy = max(calc(y0), calc(y1));
    cout << vy * (vy + 1) / 2 << endl;
}