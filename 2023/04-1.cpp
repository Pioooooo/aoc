#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line, word;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> word >> word;
        set<string> s;
        int n = 0;
        while (ss >> word) {
            if ("|" == word) {
                break;
            }
            s.insert(word);
        }
        while (ss >> word) {
            if (s.find(word) != s.end()) {
                n++;
            }
        }
        if (n) {
            sum += 1 << (n - 1);
        }
    }
    cout << sum << endl;
}