#include <bits/stdc++.h>
using namespace std;

vector<list<char>> dat;

void insert(char c, size_t pos) {
    if (pos >= dat.size()) {
        dat.resize(pos + 1);
    }
    if (c != ' ') {
        dat[pos].push_front(c);
    }
}

int main() {
    ifstream fin("in");
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            break;
        }
        for (size_t i = 0; 4 * i + 1 < line.size(); i++) {
            insert(line[4 * i + 1], i);
        }
    }
    int cnt, from, to;
    while (fin >> line >> cnt >> line >> from >> line >> to) {
        stack<char> tmp;
        for (size_t i = 0; i < cnt; i++) {
            tmp.push(dat[from - 1].back());
            dat[from - 1].pop_back();
        }
        for (size_t i = 0; i < cnt; i++) {
            dat[to - 1].push_back(tmp.top());
            tmp.pop();
        }
    }
    for (auto &&s : dat) {
        cout << s.back();
    }
    cout << endl;
}