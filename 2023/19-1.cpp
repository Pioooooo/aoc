#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
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
                v.push_back({{' ', ' ', 0}, line.substr(0, line.size() - 1)});
            }
        }
    }
    while (getline(fin, line)) {
        stringstream ss(line);
        char category, c;
        int num;
        ss >> c;
        map<char, int> rating;
        while (getline(ss, line, ',')) {
            stringstream ss2(line);
            ss2 >> category >> c >> num;
            rating[category] = num;
        }
        string cur = "in";
        while (true) {
            auto& v = ruleset[cur];
            for (int i = 0; i < v.size(); i++) {
                auto& [rule, next] = v[i];
                if (i == v.size() - 1) {
                    cur = next;
                } else {
                    auto& [category, op, num] = rule;
                    switch (op) {
                        case '<':
                            if (rating[category] < num) {
                                cur = next;
                                i = v.size();
                            }
                            break;
                        case '>':
                            if (rating[category] > num) {
                                cur = next;
                                i = v.size();
                            }
                            break;
                        default:
                            unreachable();
                    }
                }
            }
            if (cur == "A") {
                sum += ranges::fold_left(
                    rating, 0, [](int a, auto b) { return a + b.second; });
                break;
            }
            if (cur == "R") {
                break;
            }
        }
    }
    cout << sum << endl;
}
