#include <bits/stdc++.h>
using namespace std;

struct config {
    int hallway[7] = {};
    int room[2][4] = {};
    int cost = 0;

    string to_string() const {
        string ret;
        for (size_t i = 0; i < 7; i++) {
            ret += '0' + hallway[i];
        }
        ret += '\n';
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 4; j++) {
                ret += '0' + room[i][j];
            }
            ret += '\n';
        }
        return ret;
    }
};

int hallwayPos(int hallway) {
    return hallway <= 1 ? hallway
                        : (hallway >= 5 ? hallway + 4 : 2 * hallway - 1);
}

int roomPos(int roomx) { return 2 * roomx + 2; }

int calcCost(int roomx, int roomy, int hallway, int type) {
    int hallwayx = hallwayPos(hallway), realroomx = roomPos(roomx);
    return pow(10, type - 1) * (roomy + 1 + abs(hallwayx - realroomx));
}

bool connected(const config& c, int hallway, int roomx) {
    if (roomx + 1 < hallway) {
        for (size_t i = roomx + 2; i < hallway; i++) {
            if (c.hallway[i]) {
                return false;
            }
        }
    } else {
        for (size_t i = hallway + 1; i < roomx + 2; i++) {
            if (c.hallway[i]) {
                return false;
            }
        }
    }
    return true;
}

tuple<bool, size_t> insert(const config& c, int roomx) {
    if (!c.room[1][roomx]) {
        return {true, 1};
    }
    if (c.room[1][roomx] != roomx + 1) {
        return {false, !c.room[0][roomx]};
    }
    return {!c.room[0][roomx] || c.room[0][roomx] == roomx + 1, 0};
}

map<string, int> minCost;
int ans = 1e9;
auto cmp = [](const auto& l, const auto& r) { return l.second > r.second; };
priority_queue<pair<config, int>, vector<pair<config, int>>, decltype(cmp)> q;

int heuristic(const config& c) {
    int sum = 0;
    for (size_t i = 0; i < 7; i++) {
        auto& p = c.hallway[i];
        if (p) {
            sum += abs(hallwayPos(i) - roomPos(p - 1)) * pow(10, p - 1);
        }
    }
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 4; j++) {
            auto& p = c.room[i][j];
            if (p - 1 != j) {
                if (p) {
                    sum += (abs(roomPos(j) - roomPos(p - 1)) + i + 1) *
                           pow(10, p - 1);
                }
                sum += (i + 1) * pow(10, j);
            }
        }
    }
    return sum;
}

void push(const config& c) {
    if (c.cost + heuristic(c) > ans) {
        return;
    }
    auto it = minCost.find(c.to_string());
    if (it == minCost.end() || it->second > c.cost) {
        minCost[c.to_string()] = c.cost;
        int h = heuristic(c);
        if (h == 0) {
            ans = min(ans, c.cost);
            return;
        }
        q.push({c, c.cost + h});
    }
}

void moveIntoRoom(config& c) {
    bool found = true;
    while (found) {
        found = false;
        for (size_t k = 0; k < 7; k++) {
            auto& p = c.hallway[k];
            if (p && connected(c, k, p - 1)) {
                auto [empty, roomy] = insert(c, p - 1);
                if (empty) {
                    found = true;
                    c.cost += calcCost(p - 1, roomy, k, p);
                    swap(p, c.room[roomy][p - 1]);
                }
            }
        }
    }
}

void search(config c) {
    moveIntoRoom(c);
    if (!heuristic(c)) {
        ans = min(ans, c.cost);
    }
    for (size_t j = 0; j < 4; j++) {
        auto [empty, i] = insert(c, j);
        if (empty) {
            continue;
        }
        auto& p = c.room[i][j];
        for (size_t k = 0; k < 7; k++) {
            if (!c.hallway[k] && connected(c, k, j)) {
                int cost = calcCost(j, i, k, p);
                swap(p, c.hallway[k]);
                c.cost += cost;
                push(c);
                c.cost -= cost;
                swap(p, c.hallway[k]);
            }
        }
    }
}

int main() {
    ifstream fin("in");
    string line;
    (fin >> line >> line).ignore(1);
    config con;
    for (size_t i = 0; i < 2; i++) {
        getline(fin, line);
        for (size_t j = 0; j < 4; j++) {
            con.room[i][j] = line[3 + 2 * j] - 'A' + 1;
        }
    }
    push(con);
    while (!q.empty()) {
        auto [cur, h] = q.top();
        q.pop();
        if (cur.cost > minCost[cur.to_string()]) {
            continue;
        }
        search(cur);
    }
    cout << ans << endl;
}