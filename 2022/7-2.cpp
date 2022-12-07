#include <bits/stdc++.h>
using namespace std;

const int tot = 70000000, dest = 40000000;

struct directory;

struct file {
    string name;
    directory *p = nullptr;
    int size = 0;
    virtual void calcSize() {}
    virtual int calc(int least) { return tot; }
};

struct directory : virtual file {
    map<string, file *> children;
    void calcSize() override {
        for (auto &&c : children) {
            c.second->calcSize();
            size += c.second->size;
        }
    }

    int calc(int least) override {
        int ans = tot;
        for (auto &&c : children) {
            ans = min(ans, c.second->calc(least));
        }
        return size >= least ? min(ans, size) : ans;
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
    root.calcSize();
    cout << root.calc(root.size - dest) << endl;
}