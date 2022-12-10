#include <bits/stdc++.h>
using namespace std;

bool inrange(int x, int y) { return x - 1 <= y && y <= x + 1; }

int main() {
    ifstream fin("in");
    string op;
    int x = 1, tick = 0, nxt = 20;
    while (fin >> op) {
        if (op == "noop") {
            cout << (inrange(x, tick % 40) ? '#' : '.');
            tick++;
            if (!(tick % 40)) {
                cout << endl;
            }
        } else if (op == "addx") {
            int i;
            fin >> i;
            cout << (inrange(x, tick % 40) ? '#' : '.');
            tick++;
            if (!(tick % 40)) {
                cout << endl;
            }
            cout << (inrange(x, tick % 40) ? '#' : '.');
            x += i;
            tick++;
            if (!(tick % 40)) {
                cout << endl;
            }
        }
    }
}