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
        for (int i = seq.size() - 1; i >= 0; i--) {
            bool flag = true;
            for (int j = 0; j < i; j++) {
                seq[j] = seq[j + 1] - seq[j];
                if (seq[j]) {
                    flag = false;
                }
            }
            if (flag) {
                sum += accumulate(seq.begin(), seq.end(), 0ll);
                break;
            }
        }
    }
    cout << sum << endl;
}
