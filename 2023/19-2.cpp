#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0;
    string line;
    map<string, vector<pair<tuple<char, char, int>, string>>> ruleset;
    while (getline(fin, line)) {
        if (line == "") {
            break;
        }
        string label, rule;
        char category, op, c;
        int num;
        stringstream ss(line);
        getline(ss, label, '{');
        auto& v = ruleset[label];
        while (getline(ss, line, ',')) {
            if (line.find(':') != string::npos) {
                stringstream ss2(line);
                ss2 >> category >> op >> num >> c >> line;
                v.push_back({{category, op, num}, line});
            } else {
                string nxt = line.substr(0, line.size() - 1);
                v.push_back({{' ', ' ', 0}, nxt});
            }
        }
    }

    queue<pair<string, map<char, pair<int, int>>>> q;
    q.push({"in",
            {{'x', {1, 4000}},
             {'m', {1, 4000}},
             {'a', {1, 4000}},
             {'s', {1, 4000}}}}

    );
    while (!q.empty()) {
        auto [cur, rating] = q.front();
        q.pop();
        if (cur == "A") {
            sum += ranges::fold_left(rating, 1, [](long long a, auto b) {
                return a * (b.second.second - b.second.first + 1);
            });
            continue;
        }
        if (cur == "R") {
            continue;
        }
        auto& v = ruleset[cur];
        for (int i = 0; i < v.size(); i++) {
            auto& [rule, next] = v[i];
            if (i == v.size() - 1) {
                q.emplace(next, rating);
            } else {
                auto& [category, op, num] = rule;
                auto& [mn, mx] = rating[category];
                switch (op) {
                    case '<':
                        if (mx < num) {
                            q.emplace(next, rating);
                            i = v.size();
                        } else if (mn < num) {
                            auto rating2 = rating;
                            rating2[category].second = num - 1;
                            q.emplace(next, rating2);
                            rating[category].first = num;
                        }
                        break;
                    case '>':
                        if (mn > num) {
                            q.emplace(next, rating);
                            i = v.size();
                        } else if (mx > num) {
                            auto rating2 = rating;
                            rating2[category].first = num + 1;
                            q.emplace(next, rating2);
                            rating[category].second = num;
                        }
                        break;
                    default:
                        unreachable();
                }
            }
        }
    }

    cout << sum << endl;
}
