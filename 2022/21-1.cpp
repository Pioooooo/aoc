#include <bits/stdc++.h>
using namespace std;

struct op;

map<string, op> inst;

struct op {
    long long val;
    char operation = '@';
    string l, r;
    long long calc() {
        switch (operation) {
            case '@':
                return val;
            case '+':
                return inst[l].calc() + inst[r].calc();
            case '-':
                return inst[l].calc() - inst[r].calc();
            case '*':
                return inst[l].calc() * inst[r].calc();
            case '/':
                return inst[l].calc() / inst[r].calc();
        }
    }
};

int main() {
    ifstream fin("in");
    string line, word;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> word;
        word = word.substr(0, 4);
        auto &i = inst[word];
        if ('0' <= line[6] && line[6] <= '9') {
            ss >> i.val;
        } else {
            ss >> i.l >> i.operation >> i.r;
        }
    }
    op &root = inst["root"];
    cout << root.calc() << endl;
}