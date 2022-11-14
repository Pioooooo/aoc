#include <bits/stdc++.h>
using namespace std;

struct vector_t {
    int x, y, z;
    vector_t() : x(0), y(0), z(0) {}
    vector_t(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator==(const vector_t& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    vector_t operator+(const vector_t& rhs) const {
        return vector_t(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    vector_t operator-(const vector_t& rhs) const {
        return vector_t(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    int dis() const { return x * x + y * y + z * z; }

    friend int dis(const vector_t& lhs,
                   const vector_t& rhs = vector_t(0, 0, 0)) {
        return (lhs - rhs).dis();
    }
};

template <>
struct std::hash<vector_t> {
    size_t operator()(vector_t const& s) const noexcept {
        size_t h1 = hash<int>{}(s.x), h2 = hash<int>{}(s.y),
               h3 = hash<int>{}(s.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct scanner {
    vector_t loc;
    vector<vector_t> beacons;
    bool done;
    vector<size_t> dists;
    int id;
    scanner(const vector<vector_t>& beacons)
        : beacons(beacons), done(false), id(cnt++) {
        calcDist();
    }
    void calcDist() {
        for (size_t i = 0; i < beacons.size(); i++) {
            for (size_t j = 0; j < i; j++) {
                dists.push_back(dis(beacons[i], beacons[j]));
            }
        }
        sort(dists.begin(), dists.end());
    }
    static int cnt;
};
int scanner::cnt = 0;

int main() {
    ifstream fin("in");
    string line;
    vector<scanner> scanners;
    vector<vector_t> pos;
    vector<function<vector_t(vector_t&)>> perms{
        [](const vector_t& p) { return vector_t(p.x, p.y, p.z); },
        [](const vector_t& p) { return vector_t(p.x, -p.z, p.y); },
        [](const vector_t& p) { return vector_t(p.x, -p.y, -p.z); },
        [](const vector_t& p) { return vector_t(p.x, p.z, -p.y); },
        [](const vector_t& p) { return vector_t(-p.y, p.x, p.z); },
        [](const vector_t& p) { return vector_t(p.z, p.x, p.y); },
        [](const vector_t& p) { return vector_t(p.y, p.x, -p.z); },
        [](const vector_t& p) { return vector_t(-p.z, p.x, -p.y); },
        [](const vector_t& p) { return vector_t(-p.x, -p.y, p.z); },
        [](const vector_t& p) { return vector_t(-p.x, -p.z, -p.y); },
        [](const vector_t& p) { return vector_t(-p.x, p.y, -p.z); },
        [](const vector_t& p) { return vector_t(-p.x, p.z, p.y); },
        [](const vector_t& p) { return vector_t(p.y, -p.x, p.z); },
        [](const vector_t& p) { return vector_t(p.z, -p.x, -p.y); },
        [](const vector_t& p) { return vector_t(-p.y, -p.x, -p.z); },
        [](const vector_t& p) { return vector_t(-p.z, -p.x, p.y); },
        [](const vector_t& p) { return vector_t(-p.z, p.y, p.x); },
        [](const vector_t& p) { return vector_t(p.y, p.z, p.x); },
        [](const vector_t& p) { return vector_t(p.z, -p.y, p.x); },
        [](const vector_t& p) { return vector_t(-p.y, -p.z, p.x); },
        [](const vector_t& p) { return vector_t(-p.z, -p.y, -p.x); },
        [](const vector_t& p) { return vector_t(-p.y, p.z, -p.x); },
        [](const vector_t& p) { return vector_t(p.z, p.y, -p.x); },
        [](const vector_t& p) { return vector_t(p.y, -p.z, -p.x); },
    };

    while (getline(fin, line)) {
        if (line.empty()) {
            scanners.push_back(pos);
            pos.clear();
            continue;
        }
        if (line[1] == '-') {
            continue;
        }
        istringstream in(line);
        char c;
        vector_t vec;
        in >> vec.x >> c >> vec.y >> c >> vec.z;
        pos.push_back(vec);
    }
    if (!pos.empty()) {
        scanners.push_back(pos);
    }

    queue<scanner> q;
    unordered_set<vector_t> beacons{scanners[0].beacons.begin(),
                                    scanners[0].beacons.end()};
    scanners[0].done = true;
    q.push(scanners[0]);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto& s : scanners) {
            if (s.done) {
                continue;
            }
            vector<int> common;
            set_intersection(cur.dists.begin(), cur.dists.end(),
                             s.dists.begin(), s.dists.end(),
                             back_inserter(common));
            if (common.size() < 66) {
                continue;
            }
            for (auto& perm : perms) {
                unordered_map<vector_t, int> cnt;
                vector<vector_t> t;
                transform(s.beacons.begin(), s.beacons.end(), back_inserter(t),
                          perm);
                for (auto& from : cur.beacons) {
                    for (auto& to : t) {
                        cnt[from - to]++;
                    }
                }
                using pair_type = decltype(cnt)::value_type;
                auto pr =
                    max_element(cnt.begin(), cnt.end(),
                                [](const pair_type& a, const pair_type& b) {
                                    return a.second < b.second;
                                });
                if (pr->second < 12) {
                    continue;
                }
                s.loc = cur.loc + pr->first;
                s.beacons = t;
                s.done = true;
                transform(t.begin(), t.end(),
                          inserter(beacons, beacons.begin()),
                          [&](const vector_t& p) { return p + s.loc; });
                q.push(s);
                break;
            }
        }
    }
    cout << beacons.size() << endl;
}