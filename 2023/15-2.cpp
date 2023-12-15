#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    long long sum = 0;
    string line;
    list<int> boxes[256];
    map<string, list<int>::iterator> loc[256];
    while (getline(fin, line, ',')) {
        unsigned char h = 0, c;
        int i = 0;
        for (; i < line.size(); i++) {
            auto c = line[i];
            bool fl = false;
            switch (c) {
                case '\n':
                case '\r':
                    continue;
                case '-':
                case '=':
                    fl = true;
                    break;
                default:
                    h = (h + c) * 17;
                    break;
            }
            if (fl) {
                break;
            }
        }

        auto label = line.substr(0, i);
        auto it = loc[h].find(label);
        switch (line[i]) {
            case '-':
                if (it != loc[h].end()) {
                    boxes[h].erase(it->second);
                    loc[h].erase(it);
                }
                break;
            case '=': {
                int n = stoi(line.substr(i + 1));
                if (it != loc[h].end()) {
                    *it->second = n;
                } else {
                    loc[h][label] = boxes[h].insert(boxes[h].end(), n);
                }
                break;
            }
            default:
                unreachable();
        }
    }
    int i = 1;
    for (auto &box : boxes) {
        int j = 1;
        for (auto &f : box) {
            sum += i * j * f;
            j++;
        }
        i++;
    }
    cout << sum << endl;
}
