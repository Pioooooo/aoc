#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0;
    string line;
    while (getline(fin, line, ',')) {
        sum += ranges::fold_left(
            line, 0, [&](unsigned char a, unsigned char b) -> unsigned char {
                if (b == '\n' || b == '\r') {
                    return a;
                }
                return (a + b) * 17;
            });
    }
    cout << sum << endl;
}
