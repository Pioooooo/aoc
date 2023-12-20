#include <bits/stdc++.h>
using namespace std;

struct mod {
    char type;
    int reg = 0;
    map<string, bool> input;
    vector<string> output;
};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    map<string, mod> config;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> line;
        string name = line;
        if (line[0] == '%' || line[0] == '&') {
            name = line.substr(1);
        }
        auto &m = config[name];
        if (name == "broadcaster") {
            m.type = '=';
        } else {
            m.type = line[0];
        }
        ss >> line;
        while (ss >> line) {
            line = line.substr(0, line.find(','));
            m.output.push_back(line);
            config[line].input[name] = false;
        }
    }
    int i = 1000;
    array<int, 2> cnt{};
    map<int, array<int, 2>> hist;
    while (i--) {
        queue<tuple<string, string, bool>> q;
        q.emplace("broadcaster", "", false);
        while (!q.empty()) {
            auto [name, from, pulse] = q.front();
            cnt[pulse]++;
            q.pop();
            auto &m = config[name];
            switch (m.type) {
                case '=':
                    for (auto &out : m.output) {
                        q.emplace(out, name, pulse);
                    }
                    break;
                case '&': {
                    auto &r = m.input[from];
                    if (r != pulse) {
                        m.reg += pulse - r;
                        r = pulse;
                    }
                    for (auto &out : m.output) {
                        q.emplace(out, name, m.reg != m.input.size());
                    }
                    break;
                }
                case '%':
                    if (!pulse) {
                        m.reg = !m.reg;
                        for (auto &out : m.output) {
                            q.emplace(out, name, m.reg);
                        }
                    }
                    break;
                default:
                    continue;
            }
        }
        hist[i] = cnt;
        if (ranges::none_of(config, [](auto &p) { return p.second.reg; })) {
            int cycle = 1000 - i;
            int rem = 1000 % cycle;
            int times = 1000 / cycle;
            cout << (cnt[0] * times + hist[1000 - rem][0]) *
                        (cnt[1] * times + hist[1000 - rem][1])
                 << endl;
            return 0;
        }
    }
    cout << cnt[0] * cnt[1] << endl;
}
