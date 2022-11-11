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
    int mid = crab[crab.size() / 2];
    cout << accumulate(crab.begin(), crab.end(), 0, [&](int l, int r) {
        return l + abs(mid - r);
    }) << endl;
}