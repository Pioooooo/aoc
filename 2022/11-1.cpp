#include <bits/stdc++.h>
using namespace std;

struct monkey {
    int cnt = 0;
    list<long long> items;
    char op;
    int opnum, test, trueMonkey, falseMonkey;
    bool isOld;
};

int main() {
    ifstream fin("in");
    vector<monkey> monkeys;
    string line, word;
    int tmp;
    char c;
    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }
        monkey m;
        getline(fin, line);
        stringstream ss(line);
        ss >> word >> word >> tmp;
        m.items.push_back(tmp);
        while (ss >> word >> tmp) {
            m.items.push_back(tmp);
        }
        fin >> word >> word >> word >> word >> m.op >> word;
        if (word == "old") {
            m.isOld = true;
        } else {
            m.isOld = false;
            m.opnum = stoi(word);
        }
        fin >> word >> word >> word >> m.test;
        fin >> word >> word >> word >> word >> word >> m.trueMonkey;
        fin >> word >> word >> word >> word >> word >> m.falseMonkey;
        monkeys.push_back(m);
    }
    int round = 20;
    while (round--) {
        for (auto &&m : monkeys) {
            while (!m.items.empty()) {
                auto n = m.items.front();
                m.items.pop_front();
                m.cnt++;
                if (m.isOld) {
                    m.opnum = n;
                }
                switch (m.op) {
                    case '+':
                        n += m.opnum;
                        break;
                    case '*':
                        n *= m.opnum;
                        break;
                    default:
                        throw -1;
                }
                n /= 3;
                if (n % m.test == 0) {
                    monkeys[m.trueMonkey].items.push_back(n);
                } else {
                    monkeys[m.falseMonkey].items.push_back(n);
                }
            }
        }
    }
    sort(monkeys.begin(), monkeys.end(),
         [](monkey &l, monkey &r) { return l.cnt > r.cnt; });
    cout << monkeys[0].cnt * monkeys[1].cnt << endl;
}