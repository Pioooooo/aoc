#include <bits/stdc++.h>
using namespace std;

bool translate[512];

int main() {
    ifstream fin("in");
    for (size_t i = 0; i < 512; i++) {
        char c;
        fin >> c;
        translate[i] = c == '#';
    }
    size_t n = 2;
    vector<vector<bool>> img;
    string line;
    while (fin >> line) {
        img.push_back(vector(2 * n, false));
        transform(line.begin(), line.end(), back_inserter(img.back()),
                  [](char& c) { return c == '#'; });
        img.back().insert(img.back().end(), 2 * n, false);
    }
    int x = img[0].size();
    img.insert(img.begin(), 2 * n, vector(x, false));
    img.insert(img.end(), 2 * n, vector(x, false));
    int y = img.size();
    for (size_t i = 0; i < n; i++) {
        auto tmp = img;
        for (size_t j = 1; j < x - 1; j++) {
            for (size_t k = 1; k < y - 1; k++) {
                size_t index = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        index <<= 1;
                        index += img[k + dy][j + dx];
                    }
                }
                tmp[k][j] = translate[index];
            }
        }
        for (size_t j = 0; j < x; j++) {
            tmp[0][j] = tmp[y - 1][j] = tmp[1][1];
        }
        for (size_t j = 0; j < y; j++) {
            tmp[j][0] = tmp[j][x - 1] = tmp[1][1];
        }
        img = tmp;
    }
    cout << accumulate(img.begin(), img.end(), 0,
                       [](const int& i, const vector<bool>& r) {
                           return i + accumulate(r.begin(), r.end(), 0);
                       })
         << endl;
}