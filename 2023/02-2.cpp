#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string color;
        int id, n, r, g, b;
        r = g = b = 0;
        ss >> color >> id >> color;
        while (ss >> n >> color) {
            if (color.find("red") != string::npos) {
                r = max(r, n);
            } else if (color.find("green") != string::npos) {
                g = max(g, n);
            } else if (color.find("blue") != string::npos) {
                b = max(b, n);
            }
        }
        sum += r * g * b;
    }
    cout << sum << endl;
}
