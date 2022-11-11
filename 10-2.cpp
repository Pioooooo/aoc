#include <bits/stdc++.h>
using namespace std;

long long check(string line) {
    stack<char> s;
    for (char &c : line) {
        char t;
        switch (c) {
            case '(':
            case '{':
            case '[':
            case '<':
                s.push(c);
                break;
            case ')':
                t = s.top();
                s.pop();
                if (t != '(') {
                    return 0;
                }
                break;
            case '}':
                t = s.top();
                s.pop();
                if (t != '{') {
                    return 0;
                }
                break;
            case ']':
                t = s.top();
                s.pop();
                if (t != '[') {
                    return 0;
                }
                break;
            case '>':
                t = s.top();
                s.pop();
                if (t != '<') {
                    return 0;
                }
                break;
        }
    }
    long long ret = 0;
    map<char, int> score = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
    while (!s.empty()) {
        ret = ret * 5 + score[s.top()];
        s.pop();
    }

    return ret;
}

int main() {
    ifstream fin("in");
    string line;
    vector<long long> score;
    while (fin >> line) {
        long long tmp = check(line);
        if (tmp) {
            score.push_back(tmp);
        }
    }
    sort(score.begin(), score.end());
    cout << score[score.size() / 2] << endl;
}