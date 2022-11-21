#include <bits/stdc++.h>
using namespace std;

int check(string line) {
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
                    return 3;
                }
                break;
            case '}':
                t = s.top();
                s.pop();
                if (t != '{') {
                    return 1197;
                }
                break;
            case ']':
                t = s.top();
                s.pop();
                if (t != '[') {
                    return 57;
                }
                break;
            case '>':
                t = s.top();
                s.pop();
                if (t != '<') {
                    return 25137;
                }
                break;
        }
    }
    return 0;
}

int main() {
    ifstream fin("in");
    string line;
    int ans = 0;
    while (fin >> line) {
        ans += check(line);
    }
    cout << ans << endl;
}