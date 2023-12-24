#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    vector<array<double, 6>> dat;
    array<double, 6> tmp;
    char c;
    while (fin >> tmp[0] >> c >> tmp[1] >> c >> tmp[2] >> c >> tmp[3] >> c >>
           tmp[4] >> c >> tmp[5]) {
        dat.push_back(tmp);
    }
    long long l = 200000000000000, h = 400000000000000;
    for (int i = 0; i < dat.size(); i++) {
        auto &a = dat[i];
        auto &[x1, y1, z1, vx1, vy1, vz1] = a;
        for (int j = i + 1; j < dat.size(); j++) {
            auto &b = dat[j];
            auto &[x2, y2, z2, vx2, vy2, vz2] = b;
            double divisor = vy1 * vx2 - vy2 * vx1,
                   dividend =
                       vx1 * vx2 * (y2 - y1) + vy1 * vx2 * x1 - vy2 * vx1 * x2;
            if (divisor == 0) {
                continue;
            }
            double x = dividend / divisor;
            if (x < l || x > h) {
                continue;
            }
            double y = (x - x1) / vx1 * vy1 + y1;
            if (y < l || y > h) {
                continue;
            }
            if ((x - x1) / vx1 < 0 || (x - x2) / vx2 < 0) {
                continue;
            }
            sum++;
        }
    }
    cout << sum << endl;
}
