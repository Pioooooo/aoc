#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string word;
    int tot = 0;
    while (fin >> word) {
        if (word[0] != '|') {
            continue;
        }
        for (size_t i = 0; i < 4; i++) {
            fin >> word;
            int sz = word.size();
            if (sz == 2 || sz == 3 || sz == 4 || sz == 7) {
                tot++;
            }
        }
    }
    cout << tot << endl;
}