#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string color;
        int id, n;
        ss >> color >> id >> color;
        sum += id;
        while (ss >> n >> color) {
            if (color.find("red") != string::npos) {
                if (n > 12) {
                    sum -= id;
                    break;
                }
            } else if (color.find("green") != string::npos) {
                if (n > 13) {
                    sum -= id;
                    break;
                }
            } else if (color.find("blue") != string::npos) {
                if (n > 14) {
                    sum -= id;
                    break;
                }
            }
        }
    }
    cout << sum << endl;
}
