#include <bits/stdc++.h>
using namespace std;

int score(char c) { return islower(c) ? c - 'a' + 1 : c - 'A' + 27; }

int main() {
    ifstream fin("in");
    string line;
    int ans = 0;
    while (fin >> line) {
        auto mid = line.begin() + line.size() / 2;
        set<char> first{line.begin(), mid},
            second{mid, line.end()};
        vector<char> out;
        set_intersection(first.begin(), first.end(), second.begin(),
                         second.end(), back_inserter(out));
        for (auto &&c : out) {
            ans += score(c);
        }
    }
    cout << ans << endl;
}