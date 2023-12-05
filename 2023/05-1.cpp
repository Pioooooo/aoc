#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    size_t sum = 0;
    string line, word;
    vector<size_t> seeds;
    getline(fin, line);
    stringstream ss(line);
    size_t seed;
    ss >> word;
    while (ss >> seed) {
        seeds.push_back(seed);
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
        for (auto &seed : seeds) {
            for (auto [dst, src, len] : mapping) {
                if (seed >= src && seed < src + len) {
                    seed += dst - src;
                    break;
                }
            }
        }
    }
    cout << *min_element(seeds.begin(), seeds.end()) << endl;
}