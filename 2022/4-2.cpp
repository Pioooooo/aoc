#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    char deli;
    int s1, t1, s2, t2, ans = 0;
    while (fin >> s1 >> deli >> t1 >> deli >> s2 >> deli >> t2) {
        if (s2 <= t1 && t1 <= t2 || s1 <= t2 && t2 <= t1) {
            ans++;
        }
    }
    cout << ans << endl;
}