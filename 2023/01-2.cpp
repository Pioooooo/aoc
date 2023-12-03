#include <bits/stdc++.h>
using namespace std;

map<string, int> wordToDigit = {{"one", 1},   {"two", 2},   {"three", 3},
                                {"four", 4},  {"five", 5},  {"six", 6},
                                {"seven", 7}, {"eight", 8}, {"nine", 9}};
int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    while (getline(fin, line)) {
        int firstDigit = -1, lastDigit = -1;
        for (int i = 0; i < line.size(); i++) {
            string s = line.substr(i);
            int digit = -1;
            if (isdigit(s[0])) {
                digit = s[0] - '0';
            } else {
                for (auto& word : wordToDigit) {
                    if (s.substr(0, word.first.size()) == word.first) {
                        digit = word.second;
                        break;
                    }
                }
            }
            if (digit != -1) {
                if (firstDigit == -1) {
                    firstDigit = digit;
                }
                lastDigit = digit;
            }
        }
        int calibrationValue = firstDigit * 10 + lastDigit;
        sum += calibrationValue;
    }
    cout << sum << endl;
}
