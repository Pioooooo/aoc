#include <bits/stdc++.h>
using namespace std;

int dat[10000], len = 0;

int main() {
    ifstream fin("in");
    string str;
    while (fin >> str) {
        dat[len++] = stoi(str, nullptr, 2);
    }
    int bits = str.length();
    sort(dat, dat + len);
    int *start0 = dat, *start1 = lower_bound(dat, dat + len, 1 << (bits - 1)),
        *end0 = start1, *end1 = dat + len, mid0 = 0, mid1 = 1 << (bits - 1);
    if ((end0 - start0) * 2 > len) {
        swap(start0, start1);
        swap(end0, end1);
        swap(mid0, mid1);
    }  // 0 -> co2; 1 -> o2
    for (int i = bits - 2; i >= 0; i--) {
        if (start0 + 1 != end0) {
            int *mid = lower_bound(dat, dat + len, mid0 + (1 << i));
            if ((mid - start0) * 2 <= end0 - start0) {
                end0 = mid;
            } else {
                start0 = mid;
                mid0 += 1 << i;
            }
        }
        if (start1 + 1 != end1) {
            int *mid = lower_bound(dat, dat + len, mid1 + (1 << i));
            if ((mid - start1) * 2 > end1 - start1) {
                end1 = mid;
            } else {
                start1 = mid;
                mid1 += 1 << i;
            }
        }
    }
    cout << *start0 * *start1 << endl;
}