#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string line;
    int tmp = 0;
    priority_queue<int> ans;
    while (getline(fin, line)) {
        if (line.size() == 0) {
            ans.push(tmp);
            tmp = 0;
        } else {
            tmp += stoi(line);
        }
    }
    if (tmp != 0) {
        ans.push(tmp);
    }
    int ret = 0;
    for (size_t i = 0; i < 3; i++) {
        ret += ans.top();
        ans.pop();
    }
    cout << ret << endl;
}