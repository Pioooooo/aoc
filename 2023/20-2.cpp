#include <bits/stdc++.h>
using namespace std;

struct mod {
    char type;
    int reg = 0;
    map<string, int> input;
    vector<string> output;
};

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    map<string, mod> config;
    string aggre;
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
            if (line == "rx") {
                aggre = name;
            }
        }
    }
    auto cycle = config[aggre].input;
    int done = 0;
    long long i = 0;
    while (++i) {
        queue<tuple<string, string, bool>> q;
        q.emplace("broadcaster", "", false);
        while (!q.empty()) {
            auto [name, from, pulse] = q.front();
            q.pop();
            if (name == aggre && pulse && !cycle[from]) {
                cycle[from] = i;
                done++;
                if (done == cycle.size()) {
                    cout << ranges::fold_left(cycle, 1ll, [](auto a, auto b) {
                        return lcm(a, b.second);
                    }) << endl;
                    return 0;
                }
            }
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
                    if (!pulse && name == "rx") {
                        cout << i << endl;
                        return 0;
                    }
            }
        }
    }
}
