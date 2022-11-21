#include <bits/stdc++.h>
using namespace std;

char rule[26][26] = {}, first, last;

int main() {
    ifstream fin("in");
    string line;
    fin >> line;
    long long cnt[26][26] = {0};
    for (size_t i = 1; i < line.size(); i++) {
        cnt[line[i - 1] - 'A'][line[i] - 'A']++;
    }
    first = line.front(), last = line.back();

    while (fin >> line) {
        string res;
        fin >> res >> res;
        rule[line[0] - 'A'][line[1] - 'A'] = res[0];
    }
    int round = 40;
    while (round--) {
        long long cnt1[26][26] = {};
        for (size_t i = 0; i < 26; i++) {
            for (size_t j = 0; j < 26; j++) {
                if (rule[i][j] && cnt[i][j]) {
                    long long tmp = cnt[i][j];
                    cnt[i][j] = 0;
                    cnt1[i][rule[i][j] - 'A'] += tmp;
                    cnt1[rule[i][j] - 'A'][j] += tmp;
                }
            }
        }
        memcpy(cnt, cnt1, sizeof(cnt));
    }

    long long res[26] = {0};
    for (size_t i = 0; i < 26; i++) {
        res[i] = accumulate(cnt[i], cnt[i] + 26, 0ll);
    }
    res[last - 'A']++;

    sort(res, res + 26);
    cout << res[25] - *find_if(res, res + 26, [](long long &i) { return i; })
         << endl;
}