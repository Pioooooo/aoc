#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line;
    long long ans = 0;
    while (fin >> line) {
        long long tmp = 0;
        for (auto &&c : line) {
            tmp *= 5;
            switch (c) {
                case '=':
                    tmp += -2;
                    break;
                case '-':
                    tmp += -1;
                    break;
                default:
                    tmp += c - '0';
                    break;
            }
        }
        ans += tmp;
    }
    string out;
    while (ans) {
        switch (ans % 5) {
            case 3:
                out += '=';
                ans += 2;
                break;
            case 4:
                out += '-';
                ans += 1;
                break;
            default:
                out += '0' + ans % 5;
                break;
        }
        ans /= 5;
    }
    for (int i = out.size() - 1; i >= 0; i--) {
        cout << out[i];
    }
    cout << endl;
}