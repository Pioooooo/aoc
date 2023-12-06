#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long ans = 1;
    string line, word;
    vector<string> times;
    getline(fin, line);
    stringstream ss(line);
    ss >> word;
    long long n;
    while (ss >> word) {
        times.push_back(word);
    }
    long long t = stoll(accumulate(times.begin(), times.end(), string{}));
    fin >> word;
    line = "";
    for (auto &&t : times) {
        fin >> word;
        line += word;
    }
    n = stoll(line);
    long long discriminant = t * t - 4 * n;
    if (discriminant > 0) {
        if (n < 0) {
            ans = t + 1;
        } else {
            long long x = ceil((t - sqrt(discriminant)) / 2);
            if (x * (t - x) == n) {
                x++;
            }
            ans = t - 2 * x + 1;
        }
    } else if (discriminant == 0) {
        ans = !(t % 2);
    } else {
        ans = 0;
    }
    cout << ans << endl;
}
