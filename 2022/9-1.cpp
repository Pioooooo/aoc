#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> vec;

int main() {
    ifstream fin("in");
    set<vec> v;
    char c;
    int l;
    vec h = {0, 0}, t = {0, 0};
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
            if (abs(h.first - t.first) > 1 || abs(h.second - t.second) > 1) {
                t = h;
                switch (c) {
                    case 'U':
                        t.second -= 1;
                        break;
                    case 'D':
                        t.second += 1;
                        break;
                    case 'L':
                        t.first += 1;
                        break;
                    case 'R':
                        t.first -= 1;
                        break;
                }
            }
            v.insert(t);
        }
    }
    cout << v.size() << endl;
}