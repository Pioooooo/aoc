#include <bits/stdc++.h>
using namespace std;

struct v;

int compare(const v& cl, const v& cr);

struct v {
    vector<v> children;
    int num;
    v* p;
    v(v* p = nullptr, int n = -1) : p(p), num(n) {}

    int operator<=>(const v& r) const { return -compare(*this, r); }

    bool operator==(const v& r) const = default;
};

v parseLine(string line) {
    v root;
    v* cur = &root;
    int num = 0;
    for (size_t i = 1; i < line.size() - 1; i++) {
        if (line[i] == '[') {
            cur->children.push_back({cur});
            cur = &cur->children.back();
        } else if (line[i] == ']') {
            cur = cur->p;
        } else if (line[i] == ',') {
            continue;
        } else {
            while ('0' <= line[i] && line[i] <= '9') {
                num *= 10;
                num += line[i] - '0';
                i++;
            }
            cur->children.push_back({cur, num});
            num = 0;
        }
    }
    return root;
}

int compare(const v& cl, const v& cr) {
    auto l = cl, r = cr;
    if (l.num != -1 && r.num != -1) {
        if (l.num < r.num) {
            return 1;
        }
        if (l.num > r.num) {
            return -1;
        }
        return 0;
    }
    if (l.num != -1) {
        l.children.push_back({&l, l.num});
        l.num = -1;
    }
    if (r.num != -1) {
        r.children.push_back({&r, r.num});
        r.num = -1;
    }
    for (size_t i = 0; i < min(l.children.size(), r.children.size()); i++) {
        int ret = compare(l.children[i], r.children[i]);
        if (ret != 0) {
            return ret;
        }
    }
    if (l.children.size() < r.children.size()) {
        return 1;
    }
    if (l.children.size() > r.children.size()) {
        return -1;
    }
    return 0;
}

int main() {
    ifstream fin("in");
    string line;
    vector<v> lines;
    while (fin >> line) {
        lines.push_back(parseLine(line));
    }
    auto v1 = parseLine("[[2]]"), v2 = parseLine("[[6]]");
    lines.push_back(v1);
    lines.push_back(v2);
    sort(lines.begin(), lines.end());
    auto p1 = find(lines.begin(), lines.end(), v1),
         p2 = find(lines.begin(), lines.end(), v2);
    cout << (p1 - lines.begin() + 1) * (p2 - lines.begin() + 1) << endl;
}