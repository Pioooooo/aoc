#include <bits/stdc++.h>
using namespace std;

char rule[26][26] = {0};

int main() {
    ifstream fin("in");
    string line;
    fin >> line;
    list<char> p{line.begin(), line.end()};
    while (fin >> line) {
        string res;
        fin >> res >> res;
        rule[line[0] - 'A'][line[1] - 'A'] = res[0];
    }
    int round = 10;
    while (round--) {
        for (auto it = ++p.begin(); it != p.end(); it++) {
            auto it1 = it;
            it1--;
            if (rule[*it1 - 'A'][*it - 'A']) {
                p.insert(it, rule[*it1 - 'A'][*it - 'A']);
            }
        }
    }
    int cnt[26] = {0};
    for (auto &&c : p) {
        cnt[c - 'A']++;
    }
    sort(cnt, cnt + 26);
    cout << cnt[25] - *find_if(cnt, cnt + 26, [](int &i) { return i; })
         << endl;
}