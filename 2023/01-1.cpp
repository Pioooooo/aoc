#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    while (getline(fin, line)) {
        int firstDigit = -1, lastDigit = -1;
        for (char c : line) {
            if (isdigit(c)) {
                if (firstDigit == -1) {
                    firstDigit = c - '0';
                }
                lastDigit = c - '0';
            }
        }
        int calibrationValue = firstDigit * 10 + lastDigit;
        sum += calibrationValue;
    }
    cout << sum << endl;
}
