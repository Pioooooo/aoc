#include <bits/stdc++.h>
using namespace std;

struct directory;

struct file {
    string name;
    directory *p = nullptr;
    int size = 0;
    virtual int calcSize() { return 0; }
};

struct directory : virtual file {
    map<string, file *> children;
    int calcSize() override {
        int ans = 0;
        for (auto &&c : children) {
            ans += c.second->calcSize();
            size += c.second->size;
        }
        if (size <= 100000) {
            ans += size;
        }
        return ans;
    }
};

int main() {
    ifstream fin("in");
    string line;
    directory root;
    directory *cur;
    while (getline(fin, line)) {
        if (line[0] == '$') {
            if (line[2] == 'c') {
                if (line[5] == '/') {
                    cur = &root;
                } else if (line[5] == '.') {
                    cur = cur->p;
                } else {
                    string name = line.substr(5);
                    cur = dynamic_cast<directory *>(cur->children[name]);
                }
            }
        } else {
            stringstream l(line);
            string a, b;
            l >> a >> b;
            if (a[0] == 'd') {
                directory *d = new directory();
                d->name = b;
                d->p = cur;
                cur->children[b] = d;
            } else {
                file *f = new file();
                f->name = b;
                f->p = cur;
                f->size = stoi(a);
                cur->children[b] = f;
            }
        }
    }
    cout << root.calcSize() << endl;
}