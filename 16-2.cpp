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

long long decode(auto &it) {
    int ver = getInt(it, 3), id = getInt(it, 3);
    if (id == 4) {
        long long num = 0;
        bool hasNext;
        do {
            hasNext = *(it++);
            num <<= 4;
            num += getInt(it, 4);
        } while (hasNext);
        return num;
    }
    vector<long long> nums;
    if (*(it++)) {
        int n = getInt(it, 11);
        while (n--) {
            nums.push_back(decode(it));
        }
    } else {
        int n = getInt(it, 15);
        auto it1 = it + n;
        while (it < it1) {
            long long tmp = decode(it);
            nums.push_back(tmp);
        }
    }
    switch (id) {
        case 0:
            return accumulate(nums.begin(), nums.end(), 0ll);
        case 1:
            return accumulate(nums.begin(), nums.end(), 1ll,
                              multiplies<long long>());
        case 2:
            return *min_element(nums.begin(), nums.end());
        case 3:
            return *max_element(nums.begin(), nums.end());
        case 5:
            return nums[0] > nums[1];
        case 6:
            return nums[0] < nums[1];
        case 7:
            return nums[0] == nums[1];
        default:
            throw -1;
    }
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