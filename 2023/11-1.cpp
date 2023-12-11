#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    int sum = 0;
    string line;
    vector<pair<int, int>> stars;
    vector<int> col;
    vector<int> row;
    int n = 0;
    while (getline(fin, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '#') {
                stars.push_back({n, i});
                col.push_back(i);
                row.push_back(n);
            }
        }
        n++;
    }
    ranges::sort(col);
    ranges::sort(row);
    int m = col.size();

    for (int i = 0; i < 2; i++) {
        for (auto it = upper_bound(col.begin(), col.end(), col[0]); it != col.end(); it = upper_bound(it, col.end(), *it)) {
            sum += (it - col.begin()) * (col.end() - it) * ((*it - *(it - 1) - 1) * 2 + 1);
        }
        swap(col, row);
    }

    cout << sum << endl;
}
