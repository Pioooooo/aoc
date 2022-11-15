#include <bits/stdc++.h>
using namespace std;

const int dest = 21;

long long dp[dest + 10][dest + 10][2][10][10] = {};

int nextLoc(int l, int r) { return (l + r) % 10; }

int main() {
    ifstream fin("in");
    string word;
    int a, b;
    fin >> word >> word >> word >> word >> a;
    fin >> word >> word >> word >> word >> b;
    dp[0][0][0][a - 1][b - 1] = 1;
    for (int i = 0; i <= dest * 2 - 2; i++) {  // sa + sb
        for (int j = max(0, i - dest + 1); j < dest && j <= i; j++) {  // sa
            for (size_t k = 0; k < 2; k++) {                           // turn
                for (size_t l = 0; l < 10; l++) {                      // la
                    for (size_t m = 0; m < 10; m++) {                  // lb
                        for (size_t d1 = 1; d1 <= 3; d1++) {
                            for (size_t d2 = 1; d2 <= 3; d2++) {
                                for (size_t d3 = 1; d3 <= 3; d3++) {
                                    if (k) {  // b turn
                                        int t = nextLoc(m, d1 + d2 + d3);
                                        dp[j][i - j + t + 1][!k][l][t] +=
                                            dp[j][i - j][k][l][m];
                                    } else {  // a turn
                                        int t = nextLoc(l, d1 + d2 + d3);
                                        dp[j + t + 1][i - j][!k][t][m] +=
                                            dp[j][i - j][k][l][m];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    long long w[2] = {};
    for (size_t i = dest; i < dest + 10; i++) {
        for (size_t j = 0; j < dest; j++) {
            for (size_t l = 0; l < 10; l++) {
                for (size_t m = 0; m < 10; m++) {
                    w[0] += dp[i][j][1][l][m];
                    w[1] += dp[j][i][0][l][m];
                }
            }
        }
    }

    cout << *max_element(w, w + 2) << endl;
}