#include <bits/stdc++.h>
using namespace std;

map<string, int> mapping;

int get_id(string s) {
    auto it = mapping.find(s);
    if (it == mapping.end()) {
        return mapping[s] = mapping.size();
    }
    return it->second;
}

pair<int, vector<int>> globalMinCut(vector<vector<int>> mat) {
    pair<int, vector<int>> best = {INT_MAX, {}};
    int n = mat.size();
    vector<vector<int>> co(n);

    for (int i = 0; i < n; i++) {
        co[i] = {i};
    }

    for (int ph = 1; ph < n; ph++) {
        vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) {
            w[t] = INT_MIN;
            s = t, t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) {
                w[i] += mat[t][i];
            }
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        if (best.first == 3) {
            break;
        }
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) {
            mat[s][i] += mat[t][i];
        }
        for (int i = 0; i < n; i++) {
            mat[i][s] = mat[s][i];
        }
        mat[0][t] = INT_MIN;
    }

    return best;
}

int main() {
    ifstream fin("in");
    int sum = 0;
    string line, label, word;
    vector<vector<int>> edge(2000, vector<int>(2000, 0));
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> label;
        label = label.substr(0, label.size() - 1);
        while (ss >> word) {
            int u = get_id(label), v = get_id(word);
            edge[u][v] = edge[v][u] = 1;
        }
    }
    int n = mapping.size();
    edge.resize(n);
    for (int i = 0; i < n; i++) edge[i].resize(n);
    auto [mincut, cut] = globalMinCut(edge);
    cout << cut.size() * (n - cut.size()) << endl;
}
