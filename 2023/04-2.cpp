#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line, word;
    vector<string> lines;
    vector<int> cnt;
    while (getline(fin, line)) {
        lines.push_back(line);
        cnt.push_back(1);
    }
    int l = lines.size();
    for (int i = 0; i < l; i++) {
        stringstream ss(lines[i]);
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
        for (int j = i + 1; j < min(l, i + n + 1); j++) {
            cnt[j] += cnt[i];
        }
        sum += cnt[i];
    }
    cout << sum << endl;
}