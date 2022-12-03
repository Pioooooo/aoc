#include <bits/stdc++.h>
using namespace std;

int score(char c) { return islower(c) ? c - 'a' + 1 : c - 'A' + 27; }

int main() {
    ifstream fin("in");
    string line1, line2, line3;
    int ans = 0;
    while (fin >> line1 >> line2 >> line3) {
        set<char> s1{line1.begin(), line1.end()},
            s2{line2.begin(), line2.end()}, s3{line3.begin(), line3.end()};
        vector<char> out1, out2;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                         back_inserter(out1));
        set_intersection(out1.begin(), out1.end(), s3.begin(), s3.end(),
                         back_inserter(out2));
        for (auto &&c : out2) {
            ans += score(c);
        }
    }
    cout << ans << endl;
}