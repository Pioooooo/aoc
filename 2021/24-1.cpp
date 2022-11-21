#include <bits/stdc++.h>
using namespace std;

struct ALU {
    enum OP { INP, ADD, MUL, DIV, MOD, EQL };
    struct operation {
        OP opcode;
        struct operand {
            bool isConst = {};
            int val = {};
            friend istream &operator>>(istream &in, operand &opr) {
                string tmp;
                in >> tmp;
                if (isalpha(tmp[0])) {
                    opr.isConst = false;
                    opr.val = tmp[0] - 'w';
                } else {
                    opr.isConst = true;
                    opr.val = stoi(tmp);
                }
                return in;
            }
        } lhs = {}, rhs = {};

        friend istream &operator>>(istream &in, operation &op) {
            string tmp;
            in >> tmp;
            if (tmp == "") {
                return in;
            }
            if (tmp == "inp") {
                op.opcode = OP::INP;
                return in >> op.lhs;
            }
            if (tmp == "add") {
                op.opcode = OP::ADD;
            }
            if (tmp == "mul") {
                op.opcode = OP::MUL;
            }
            if (tmp == "div") {
                op.opcode = OP::DIV;
            }
            if (tmp == "mod") {
                op.opcode = OP::MOD;
            }
            if (tmp == "eql") {
                op.opcode = OP::EQL;
            }
            return in >> op.lhs >> op.rhs;
        }
    };

    int reg[4] = {};
    vector<operation> program;

    friend istream &operator>>(istream &in, ALU &alu) {
        operation op;
        while (in >> op) {
            alu.program.push_back(op);
        }
        return in;
    }

    string input = {};
    int idx = {};

    int getInput() { return input[idx++] - '0'; }

    int toInt(operation::operand x) {
        if (x.isConst) {
            return x.val;
        }
        return reg[x.val];
    }

    int &getReg(operation::operand x) {
        if (x.isConst) {
            throw -1;
        }
        return reg[x.val];
    }

    int *const run(long long ipt) {
        memset(reg, 0, sizeof(reg));
        input = to_string(ipt);
        idx = 0;
        for (auto &&op : program) {
            switch (op.opcode) {
                case OP::INP:
                    getReg(op.lhs) = getInput();
                    break;
                case OP::ADD:
                    getReg(op.lhs) += toInt(op.rhs);
                    break;
                case OP::MUL:
                    getReg(op.lhs) *= toInt(op.rhs);
                    break;
                case OP::DIV:
                    getReg(op.lhs) /= toInt(op.rhs);
                    break;
                case OP::MOD:
                    getReg(op.lhs) %= toInt(op.rhs);
                    break;
                case OP::EQL:
                    getReg(op.lhs) = getReg(op.lhs) == toInt(op.rhs);
                    break;
            }
        }

        return reg;
    }
};

int main() {
    ifstream fin("in");
    ALU alu;
    fin >> alu;
    auto &program = alu.program;
    int len = program.size() / 14;
    int ans[14];
    stack<pair<int, int>> s;
    for (size_t i = 0; i < 14; i++) {
        if (program[len * i + 4].rhs.val == 1) {
            s.push({i, program[len * i + 15].rhs.val});
        } else {
            auto [ind, c] = s.top();
            s.pop();
            c += program[len * i + 5].rhs.val;
            if (c > 0) {
                ans[ind] = 9 - c;
                ans[i] = 9;
            } else {
                ans[ind] = 9;
                ans[i] = 9 + c;
            }
        }
    }
    for (size_t i = 0; i < 14; i++) {
        cout << ans[i];
    }
    cout << endl;
}