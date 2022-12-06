#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string dat;
    fin >> dat;
    for (size_t i = 0; i < dat.size() - 3; i++) {
        set<char> s;
        for (size_t j = 0; j < 4; j++) {
            s.insert(dat[i + j]);
        }
        if (s.size() == 4) {
            cout << i + 4 << endl;
            break;
        }
    }
}