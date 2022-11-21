#include <bits/stdc++.h>
using namespace std;

struct Pair {
    int n;
    Pair *l, *r, *p;
    Pair(int n, Pair* const& p = nullptr)
        : n(n), l(nullptr), r(nullptr), p(p) {}
    Pair(const Pair& _l, const Pair& _r) : n(-1) {
        l = new Pair(0, this);
        r = new Pair(0, this);
        *l = _l;
        *r = _r;
    }
    Pair(Pair* const& l, Pair* const& r, Pair* const& p = nullptr)
        : n(-1), l(l), r(r), p(p) {
        l->p = this;
        r->p = this;
    }
    Pair(const char*& str, Pair* const& p = nullptr) : p(p) {
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

    bool isNum() const { return n != -1; }
    bool hasChild() const { return n == -1; }

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

    int magnitude() const {
        if (isNum()) {
            return n;
        }
        return 3 * l->magnitude() + 2 * r->magnitude();
    }

    friend ostream& operator<<(ostream& o, const Pair& p) {
        if (p.isNum()) {
            return o << p.n;
        }
        return o << '[' << *p.l << ',' << *p.r << ']';
    }

    friend Pair operator+(const Pair& l, const Pair& r) {
        Pair ret(l, r);
        while (ret.explode() || ret.split())
            ;
        return ret;
    }

    Pair& operator=(const Pair& rhs) {
        if (rhs.isNum()) {
            if (hasChild()) {
                delete l;
                delete r;
                l = r = nullptr;
            }
            n = rhs.n;
        } else {
            n = -1;
            if (hasChild()) {
                delete l;
                delete r;
                l = r = nullptr;
            }
            l = new Pair(0, this);
            r = new Pair(0, this);
            *l = *rhs.l;
            *r = *rhs.r;
        }
        return *this;
    }
};

int main() {
    ifstream fin("in");
    string line;
    vector<Pair> nums;
    while (fin >> line) {
        auto str = line.c_str();
        nums.push_back({str});
    }
    int ans = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = i + 1; j < nums.size(); j++) {
            ans = max({ans, (nums[i] + nums[j]).magnitude(),
                       (nums[j] + nums[i]).magnitude()});
        }
    }
    cout << ans << endl;
}