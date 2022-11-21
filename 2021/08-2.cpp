#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("in");
    string word;
    int tot = 0;

    while (fin >> word) {
        vector<string> words;
        sort(word.begin(), word.end());
        words.push_back(word);
        for (size_t i = 0; i < 9; i++) {
            fin >> word;
            sort(word.begin(), word.end());
            words.push_back(word);
        }
        sort(words.begin(), words.end(),
             [](string& l, string& r) { return l.size() <= r.size(); });
        int num[10];
        string t1 = words[0], t7 = words[1], t4 = words[2], t8 = words[9];
        num[0] = 1, num[1] = 7, num[2] = 4, num[9] = 8;
        for (size_t i = 6; i < 9; i++) {
            string& tmp = words[i];
            char c;
            remove_copy_if(t8.begin(), t8.end(), &c, [&](char& c) {
                return tmp.find(c) != string::npos;
            });  // 8-0,6,9
            if (t1.find(c) != string::npos) {
                num[i] = 6;
            } else if (t4.find(c) != string::npos) {
                num[i] = 0;
            } else {
                num[i] = 9;
            }
        }
        for (size_t i = 3; i < 6; i++) {
            string& tmp = words[i];
            char c[4] = {0};
            remove_copy_if(tmp.begin(), tmp.end(), c, [&](char& c) {
                return t1.find(c) != string::npos;
            });  // 2,3,5-1
            if (strlen(c) == 3) {
                num[i] = 3;
            } else {
                char c[4] = {0};
                remove_copy_if(tmp.begin(), tmp.end(), c, [&](char& c) {
                    return t4.find(c) != string::npos;
                });  // 2,3,5-4
                if (strlen(c) == 2) {
                    num[i] = 5;
                } else {
                    num[i] = 2;
                }
            }
        }

        fin >> word;
        for (size_t i = 0; i < 4; i++) {
            fin >> word;
            sort(word.begin(), word.end());
            tot += num[find(words.begin(), words.end(), word) - words.begin()] *
                   pow(10, 3 - i);
        }
    }
    cout << tot << endl;
}