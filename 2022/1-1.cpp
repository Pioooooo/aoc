#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line;
    int ans = 0, tmp = 0;
    while (getline(fin, line)) {
        if (line.size() == 0) {
            ans = max(ans, tmp);
            tmp = 0;
        } else {
            tmp += stoi(line);
        }
    }
    if (tmp != 0) {
        ans = max(ans, tmp);
    }
    cout << ans << endl;
}