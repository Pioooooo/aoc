#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int ans = 1;
    string line, word;
    vector<int> times;
    getline(fin, line);
    stringstream ss(line);
    ss >> word;
    int n;
    while (ss >> n) {
        times.push_back(n);
    }
    fin >> word;
    for (auto &&t : times) {
        int cur;
        fin >> n;
        int discriminant = t * t - 4 * n;
        if (discriminant > 0) {
            if (n < 0) {
                cur = t + 1;
            } else {
                int x = ceil((t - sqrt(discriminant)) / 2);
                if (x * (t - x) == n) {
                    x++;
                }
                cur = t - 2 * x + 1;
            }
        } else if (discriminant == 0) {
            cur = !(t % 2);
        } else {
            cur = 0;
        }
        ans *= cur;
    }

    cout << ans << endl;
}
