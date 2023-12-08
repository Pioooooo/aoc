#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line, inst;
    getline(fin, inst);
    getline(fin, line);
    map<string, pair<string, string>> m;
    vector<string> s;
    while (getline(fin, line)) {
        string c = line.substr(0, 3);
        if (c[2] == 'A') {
            s.push_back(c);
        }
        m[c] = {line.substr(7, 3), line.substr(12, 3)};
    }
    cout << ranges::fold_left(s | views::transform([&](string cur) {
                                  long long i = 0;
                                  while (true) {
                                      auto &[l, r] = m[cur];
                                      if (inst[i++ % inst.size()] == 'R') {
                                          cur = r;
                                      } else {
                                          cur = l;
                                      }
                                      if (cur[2] == 'Z') {
                                          return i;
                                      }
                                  }
                              }),
                              1ll, [](long long a, long long b) { return lcm(a, b); })
         << endl;
}
