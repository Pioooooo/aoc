#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string op;
    int x = 1, tick = 0, nxt = 20, ans = 0;
    while (fin >> op) {
        if (op == "noop") {
            if (tick + 1 >= nxt) {
                ans += nxt * x;
                nxt += 40;
            }
            tick++;
        } else if (op == "addx") {
            int i;
            fin >> i;
            if (tick + 2 >= nxt) {
                ans += nxt * x;
                nxt += 40;
            }
            x += i;
            tick += 2;
        }
    }
    cout << ans << endl;
}