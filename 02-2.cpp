#include <bits/stdc++.h>
using namespace std;

enum OP { UP, DOWN, FORWARD };

map<string, OP> opMap = {{"up", UP}, {"down", DOWN}, {"forward", FORWARD}};

int main() {
    ifstream fin("in");
    int x = 0, y = 0, aim = 0, len;
    string op;
    while (fin >> op) {
        fin >> len;
        switch (opMap[op]) {
            case UP:
                aim -= len;
                break;
            case DOWN:
                aim += len;
                break;
            case FORWARD:
                x += len;
                y += aim * len;
                break;
            default:
                throw -1;
        }
    }
    cout << x * y << endl;
}