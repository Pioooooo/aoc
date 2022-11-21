#include <bits/stdc++.h>
using namespace std;

int dep[20000], len = 0;

int main() {
    ifstream fin("in");
    while (fin >> dep[len++]) {
    }
    int tot = 0;
    for (size_t i = 3; i < len; i++) {
        tot += dep[i] > dep[i - 3];
    }
    cout << tot << endl;
}