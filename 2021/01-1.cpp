#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int prev, cur, tot = 0;
    fin >> prev;
    while (fin >> cur) {
        tot += cur > prev;
        prev = cur;
    }
    cout << tot << endl;
}