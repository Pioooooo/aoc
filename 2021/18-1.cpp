#include <bits/stdc++.h>
using namespace std;

struct Pair {
    int n;
    Pair *l, *r, *p;
    Pair(int n, Pair* p = nullptr) : n(n), l(nullptr), r(nullptr), p(p) {}
    Pair(Pair* l, Pair* r, Pair* p = nullptr) : n(-1), l(l), r(r), p(p) {
        l->p = this;
        r->p = this;
    }
    Pair(const char*& str, Pair* p = nullptr) : p(p) {
        if (*str == '[') {
            n = -1;
            l = new Pair(++str, this);
            r = new Pair(str, this);
        } else {
            n = 0;
            while (isdigit(*str)) {
                n *= 10;
                n += *str++ - '0';
            }
        }
        str++;
    }

    bool explode(size_t layer = 1) {
        if (isNum()) {
            return false;
        }
        if (l->explode(layer + 1) || r->explode(layer + 1)) {
            return true;
        }
        if (layer > 4) {
            int lnum = l->n, rnum = r->n;
            Pair* cur = this;
            while (cur->p != nullptr && cur->p->r == cur) {
                cur = cur->p;
            }
            if (cur->p != nullptr) {
                cur = cur->p->r;
                while (cur->hasChild()) {
                    cur = cur->l;
                }
                cur->n += rnum;
            }
            cur = this;
            while (cur->p != nullptr && cur->p->l == cur) {
                cur = cur->p;
            }
            if (cur->p != nullptr) {
                cur = cur->p->l;
                while (cur->hasChild()) {
                    cur = cur->r;
                }
                cur->n += lnum;
            }
            delete l;
            delete r;
            l = r = nullptr;
            n = 0;
            return true;
        }
        return false;
    }

    bool isNum() { return n != -1; }
    bool hasChild() { return n == -1; }

    bool split() {
        if (n > 9) {
            l = new Pair(n / 2, this);
            r = new Pair(n - n / 2, this);
            n = -1;
            return true;
        }
        if (hasChild()) {
            return l->split() || r->split();
        }
        return false;
    }

    int magnitude() {
        if (isNum()) {
            return n;
        }
        return 3 * l->magnitude() + 2 * r->magnitude();
    }

    friend ostream& operator<<(ostream& o, Pair p) {
        if (p.isNum()) {
            return o << p.n;
        }
        return o << '[' << *p.l << ',' << *p.r << ']';
    }

    friend Pair* add(Pair* const& l, Pair* const& r) {
        Pair* ret = new Pair(l, r);
        while (ret->explode() || ret->split())
            ;
        return ret;
    }
};

int main() {
    ifstream fin("in");
    string line;
    fin >> line;
    auto str = line.c_str();
    auto root = new Pair(str);
    while (fin >> line) {
        auto str = line.c_str();
        auto tmp = new Pair(str);
        root = add(root, tmp);
    }
    cout << root->magnitude() << endl;
}