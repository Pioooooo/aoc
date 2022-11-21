#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string str;
    fin >> str;
    int cnt = 1;
    vector<int> ones(str.begin(), str.end());
    for_each(ones.begin(), ones.end(), [](int &i) { i -= '0'; });
    while (fin >> str) {
        for (int i = 0; i < str.length(); i++) {
            ones[i] += str[i] == '1';
        }
        cnt++;
    }
    for_each(ones.begin(), ones.end(), [&](int &i) {
        if (i * 2 == cnt) {
            throw -1;
        }
        i = '0' + (i * 2 > cnt);
    });
    int gamma = stoi(string(ones.begin(), ones.end()), nullptr, 2),
        epsilon = (1 << ones.size()) - gamma - 1;
    cout << gamma * epsilon << endl;
}