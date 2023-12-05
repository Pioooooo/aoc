#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    size_t sum = 0;
    string line, word;
    queue<pair<size_t, size_t>> seeds;
    getline(fin, line);
    stringstream ss(line);
    size_t a, b;
    ss >> word;
    while (ss >> a >> b) {
        seeds.emplace(a, b);
    }
    getline(fin, line);
    while (getline(fin, line)) {
        vector<tuple<size_t, size_t, size_t>> mapping;
        while (getline(fin, line) && !line.empty()) {
            size_t dst, src, len;
            stringstream ss(line);
            ss >> dst >> src >> len;
            mapping.emplace_back(dst, src, len);
        }
        queue<pair<size_t, size_t>> new_seeds;
        while (!seeds.empty()) {
            auto [s, t] = seeds.front();
            seeds.pop();
            bool done = false;
            for (auto [dst, src, len] : mapping) {
                if (src + len <= s || s + t <= src) {
                    continue;
                }
                if (src <= s) {
                    if (s + t <= src + len) {
                        new_seeds.emplace(s + dst - src, t);
                        done = true;
                        break;
                    }
                    new_seeds.emplace(s + dst - src, src + len - s);
                    t = s + t - src - len;
                    s = src + len;
                } else {
                    if (s + t <= src + len) {
                        new_seeds.emplace(dst, s + t - src);
                        t = src - s;
                    } else {
                        new_seeds.emplace(dst, len);
                        t = src - s;
                        seeds.emplace(src + len, s + t - src - len);
                    }
                }
            }
            if (!done) {
                new_seeds.emplace(s, t);
            }
        }
        seeds = new_seeds;
    }

    size_t min_seed = seeds.front().first;
    seeds.pop();
    while (!seeds.empty()) {
        min_seed = min(min_seed, seeds.front().first);
        seeds.pop();
    }
    cout << min_seed << endl;
}