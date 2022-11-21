#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int i;
    char c;
    vector<int> crab;
    while (fin >> i) {
        fin >> c;
        crab.push_back(i);
    }
    sort(crab.begin(), crab.end());
    auto f = [](int m) {
        return [=](int l, int r) {
            return l + [=](int x) { return x * (x + 1) / 2; }(abs(m - r));
        };
    };
    auto calc = [&](int i) {
        return accumulate(crab.begin(), crab.end(), 0, f(i));
    };
    int l = crab[0], r = *crab.rbegin();
    while (l != r) {
        int mid = (l + r) / 2;
        if (calc(mid) > calc(mid + 1)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << calc(l) << endl;
}