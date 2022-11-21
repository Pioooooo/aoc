#include <bits/stdc++.h>
using namespace std;
using namespace std::placeholders;

struct vec {
    int x, y, z;
    vec() = default;
    vec(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator==(const vec &r) const {
        return tie(x, y, z) == tie(r.x, r.y, r.z);
    }
    bool operator>(const vec &r) const { return x > r.x || y > r.y || z > r.z; }
    bool operator<(const vec &r) const { return r > *this; }
};

struct cuboid {
    vec s, t;
    bool on;
    cuboid() = default;
    cuboid(int x1, int y1, int z1, int x2, int y2, int z2, bool on = false)
        : s(x1, y1, z1), t(x2, y2, z2), on(on) {}
    long long size() const {
        return 1ll * (t.x - s.x + 1) * (t.y - s.y + 1) * (t.z - s.z + 1);
    }
};

auto isOverlapped = [](const cuboid &a,
                       const cuboid &b) -> tuple<bool, cuboid> {
    if (a.s > b.t || b.s > a.t) {
        return {false, cuboid()};
    }
    auto x1 = max(a.s.x, b.s.x), x2 = min(a.t.x, b.t.x), y1 = max(a.s.y, b.s.y),
         y2 = min(a.t.y, b.t.y), z1 = max(a.s.z, b.s.z), z2 = min(a.t.z, b.t.z);
    return {true, cuboid(x1, y1, z1, x2, y2, z2)};
};

long long countUnchanged(const cuboid &c, const vector<cuboid> &ls,
                         size_t ind) {
    long long ret = c.size();
    vector<cuboid> tmp;
    for (size_t i = ind; i < ls.size(); i++) {
        auto [overlapped, overlap] = isOverlapped(c, ls[i]);
        if (overlapped) {
            tmp.push_back(overlap);
        }
    }
    for (size_t i = 0; i < tmp.size(); i++) {
        ret -= countUnchanged(tmp[i], tmp, i + 1);
    }
    return ret;
}

int main() {
    ifstream fin("in");
    string word;
    char c;
    vector<cuboid> inst;
    while (fin >> word >> c >> c) {
        int s[3], t[3];
        fin >> s[0];
        fin.ignore(2) >> t[0];
        fin.ignore(3) >> s[1];
        fin.ignore(2) >> t[1];
        fin.ignore(3) >> s[2];
        fin.ignore(2) >> t[2];
        inst.push_back({s[0], s[1], s[2], t[0], t[1], t[2], word.size() == 2});
    }
    long long ans = 0;
    for (size_t i = 0; i < inst.size(); i++) {
        if (inst[i].on) {
            ans += countUnchanged(inst[i], inst, i + 1);
        }
    }
    cout << ans << endl;
}