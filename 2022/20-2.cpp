#include <bits/stdc++.h>
using namespace std;

vector<long long> file;
vector<int> ind;

void print() {
    for (auto &&i : ind) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    ifstream fin("in");
    long long n;
    while (fin >> n) {
        file.push_back(n * 811589153);
        ind.push_back(ind.size());
    }
    for (size_t i = 0; i < 10; i++) {
        for (size_t i = 0; i < ind.size(); i++) {
            int pos = ind.erase(find(ind.begin(), ind.end(), i)) - ind.begin();
            int sz = ind.size();
            int newPos = ((pos + file[i]) % sz + sz) % sz;
            ind.insert(ind.begin() + newPos, i);
        }
    }
    long long ans = 0;
    int zero = find(ind.begin(), ind.end(),
                    find(file.begin(), file.end(), 0) - file.begin()) -
               ind.begin();
    for (size_t i = 1000; i <= 3000; i += 1000) {
        ans += file[ind[(zero + i) % ind.size()]];
    }
    cout << ans << endl;
}