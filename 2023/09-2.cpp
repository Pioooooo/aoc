#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0, n;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<long long> seq;
        while (ss >> n) {
            seq.push_back(n);
        }
        for (int i = 0; i < seq.size(); i++) {
            bool flag = true;
            for (int j = seq.size() - 1; j > i; j--) {
                seq[j] = seq[j] - seq[j - 1];
                if (seq[j]) {
                    flag = false;
                }
            }
            if (flag) {
                sum += ranges::fold_right_last(
                           seq | ranges::views::take(i + 1),
                           [](auto a, auto b) { return a - b; })
                           .value_or(0);

                break;
            }
        }
    }
    cout << sum << endl;
}
