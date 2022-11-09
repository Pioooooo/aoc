#include <bits/stdc++.h>
using namespace std;

typedef array<array<int, 5>, 5> board_t;

bool check(board_t& board, size_t x, size_t y) {
    if (all_of(board[x].begin(), board[x].end(),
               [&](auto& x) { return x == -1; })) {
        return true;
    }
    for (size_t i = 0; i < 5; i++) {
        if (board[i][y] != -1) {
            return false;
        }
    }
    return true;
}

int sum(board_t& board) {
    return accumulate(
        board.begin(), board.end(), 0, [](auto lhs, const auto& rhs) {
            return accumulate(rhs.begin(), rhs.end(), lhs,
                              [](auto lhs, const auto& rhs) {
                                  return lhs + (rhs == -1 ? 0 : rhs);
                              });
        });
}

int main() {
    ifstream fin("in");
    string nums;
    fin >> nums;
    fin.exceptions(ios_base::eofbit);

    vector<board_t> boards;
    try {
        while (true) {
            board_t board;
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    fin >> board[i][j];
                }
            }
            boards.push_back(board);
        }
    } catch (ios_base::failure& e) {
    }
    string deli = ",";
    for (const auto str : views::split(nums, deli)) {
        int num = stoi(string{str.begin(), str.end()});
        for (auto& board : boards) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (board[i][j] == num) {
                        board[i][j] = -1;
                        if (check(board, i, j)) {
                            cout << num * sum(board) << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    throw -1;
}