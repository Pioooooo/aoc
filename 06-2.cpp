#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long fish[9] = {0};
    char num;
    while (fin >> num) {
        fish[num - '0']++;
        fin.ignore();
    }
    int days = 256;
    while (days--) {
        long long tmp = fish[0];
        for (size_t i = 0; i < 9; i++) {
            fish[i] = fish[i + 1];
        }
        fish[8] = tmp;
        fish[6] += tmp;
    }
    cout << accumulate(fish, fish + 9, 0ll) << endl;
}