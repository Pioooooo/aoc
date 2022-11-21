#include <bits/stdc++.h>
using namespace std;

int getInt(auto &it, size_t len) {
    int ret = 0;
    while (len--) {
        ret <<= 1;
        int tmp = *(it++);
        ret += tmp;
    }
    return ret;
};

int decode(auto &it) {
    int ver = getInt(it, 3), id = getInt(it, 3);
    if (id == 4) {
        bool hasNext;
        do {
            hasNext = *(it++);
            getInt(it, 4);
        } while (hasNext);
    } else {
        if (*(it++)) {
            int n = getInt(it, 11);
            while (n--) {
                ver += decode(it);
            }
        } else {
            int n = getInt(it, 15);
            auto it1 = it + n;
            while (it < it1) {
                ver += decode(it);
            }
        }
    }
    return ver;
};

int main() {
    ifstream fin("in");
    string line;
    fin >> line;
    auto bitstream = line | views::transform([](const char &c) {
                         auto str =
                             bitset<4>{stoi(string{c}, 0, 16)}.to_string(0, 1);
                         return vector<bool>{str.begin(), str.end()};
                     }) |
                     views::join | views::common;
    vector<bool> bits{bitstream.begin(), bitstream.end()};

    auto it = bits.begin();
    cout << decode(it) << endl;
}