#include <bits/stdc++.h>
using namespace std;

vector<int> file;
vector<int> ind;

int main() {
    ifstream fin("in");
    int n;
    while (fin >> n) {
        file.push_back(n);
        ind.push_back(ind.size());
    }
    for (size_t i = 0; i < ind.size(); i++) {
        int pos = ind.erase(find(ind.begin(), ind.end(), i)) - ind.begin();
        int sz = ind.size();
        int newPos = ((pos + file[i]) % sz + sz) % sz;
        ind.insert(ind.begin() + newPos, i);
    }
    int ans = 0, zero = find(ind.begin(), ind.end(),
                             find(file.begin(), file.end(), 0) - file.begin()) -
                        ind.begin();
    for (size_t i = 1000; i <= 3000; i += 1000) {
        ans += file[ind[(zero + i) % ind.size()]];
    }
    cout << ans << endl;
}