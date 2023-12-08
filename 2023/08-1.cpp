#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line, inst;
    getline(fin, inst);
    getline(fin, line);
    map<string, pair<string, string>> m;
    while (getline(fin, line)) {
        m[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }
    int i = 0;
    string cur = "AAA";
    while (true) {
        auto &[l, r] = m[cur];
        if (inst[i++ % inst.size()] == 'R') {
            cur = r;
        } else {
            cur = l;
        }
        if (cur == "ZZZ") {
            break;
        }
    }

    cout << i << endl;
}
