#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> vec;

vec operator-(const vec& l, const vec& r) {
    return {l.first - r.first, l.second - r.second};
}

int num(int d) { return d == 0 ? 0 : d / abs(d); }

void update(vec& h, vec& t) {
    vec d = h - t;
    if (abs(d.first) > 1 || abs(d.second) > 1) {
        t.first += num(d.first);
        t.second += num(d.second);
    }
}

int main() {
    ifstream fin("in");
    set<vec> v;
    char c;
    int l;
    vec rope[10], &h = rope[0], &t = rope[9];
    v.insert(t);
    while (fin >> c >> l) {
        for (size_t i = 0; i < l; i++) {
            switch (c) {
                case 'U':
                    h.second += 1;
                    break;
                case 'D':
                    h.second -= 1;
                    break;
                case 'L':
                    h.first -= 1;
                    break;
                case 'R':
                    h.first += 1;
                    break;
            }
            for (size_t j = 0; j < 9; j++) {
                update(rope[j], rope[j + 1]);
            }
            v.insert(t);
        }
    }
    cout << v.size() << endl;
}