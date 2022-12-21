#include <bits/stdc++.h>
using namespace std;

struct op;

map<string, op> inst;

struct op {
    long long val;
    char operation = '@';
    string l, r;
    int validOther = 0;  // 0->invalid, 1->l, 2->r
    long long other;

    long long calc() {
        if (operation == '@') {
            return val;
        }
        long long ll, rr;
        try {
            if (l == "humn") {
                throw -1;
            }
            ll = inst[l].calc();
        } catch (const int &e) {
            validOther = 2;
            rr = other = inst[r].calc();
            if (operation != '=') {
                throw -1;
            }
        }
        try {
            if (r == "humn") {
                throw -1;
            }
            rr = inst[r].calc();
        } catch (const int &e) {
            validOther = 1;
            ll = other = inst[l].calc();
            if (operation != '=') {
                throw -1;
            }
        }
        switch (operation) {
            case '+':
                return ll + rr;
            case '-':
                return ll - rr;
            case '*':
                return ll * rr;
            case '/':
                return ll / rr;
        }
        // case '='
        return inst[validOther == 1 ? r : l].rCalc(other);
    }

    long long rCalc(long long expected) {
        switch (operation) {
            case '@':  // humn only
                return expected;
            case '+':
                return inst[validOther == 1 ? r : l].rCalc(expected - other);
            case '-':
                if (validOther == 1) {
                    return inst[r].rCalc(other - expected);
                } else {
                    return inst[l].rCalc(expected + other);
                }
            case '*':
                return inst[validOther == 1 ? r : l].rCalc(expected / other);
            case '/':
                if (validOther == 1) {
                    return inst[r].rCalc(other / expected);
                } else {
                    return inst[l].rCalc(expected * other);
                }
        }
        throw -1;
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
    root.operation = '=';
    cout << root.calc() << endl;
}