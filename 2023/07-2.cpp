#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0, bid;

    string sz = "J23456789TQKA", word;
    auto rank = [](const string& h) {
        map<char, int> m;
        for (char c : h) {
            m[c]++;
        }
        priority_queue<int> pq;
        int j = 0;
        for (auto&& [k, v] : m) {
            if (k == 'J') {
                j = v;
            } else {
                pq.push(v);
            }
        }
        int n = j;
        if (!pq.empty()) {
            n += pq.top();
            pq.pop();
        }
        switch (n) {
            case 5:
                return 7;
            case 4:
                return 6;
            case 3:
                if (pq.top() == 2) {
                    return 5;
                } else {
                    return 4;
                }
            case 2:
                if (pq.top() == 2) {
                    return 3;
                } else {
                    return 2;
                }
            default:
                return 1;
        }
    };
    auto cmp = [&](pair<string, int> a, pair<string, int> b) {
        string &h1 = a.first, h2 = b.first;
        int r1 = rank(a.first), r2 = rank(b.first);
        if (r1 != r2) {
            return r1 > r2;
        }
        int i = 0;
        while (h1[i] == h2[i]) {
            i++;
        }
        return sz.find(h1[i]) > sz.find(h2[i]);
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)>
        pq(cmp);
    while (fin >> word >> bid) {
        pq.emplace(word, bid);
    }
    bid = 1;
    while (!pq.empty()) {
        auto [h, b] = pq.top();
        pq.pop();
        sum += b * bid++;
    }
    cout << sum << endl;
}
