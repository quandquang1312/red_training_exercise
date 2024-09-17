// https://codeforces.com/problemset/problem/25/D

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y])
            swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y])
            ++rank[y];
        setSize[y] += setSize[x];
        --numSets;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    vector<pair<int, int>> roads;
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        roads.push_back({u, v});
    }

    UnionFind UF(n + 1);

    vector<pair<int, int>> rm;
    vector<set<int>> parent(n + 1);
    vector<bool> visited(n + 1, false);

    for (auto &[u, v] : roads) {
        visited[u] = true;
        visited[v] = true;

        if (UF.isSameSet(u, v)) {
            rm.push_back({u, v});
        } else {
            UF.unionSet(u, v);
        }
    }

    for (int i=1; i<=n; i++) {
        int p = UF.findSet(i);
        parent[p].insert(i);
    }

    vector<int> nodes;
    for (int i=1; i<=n; i++) {
        if (parent[i].size() != 0) {
            nodes.push_back(*parent[i].begin());
        } else if (visited[i] == false) {
            nodes.push_back(i);
        }
    }

    vector<pair<int, int>> add;
    for (int i=0; i<nodes.size() - 1; i++) {
        add.push_back({nodes[i % nodes.size()], nodes[(i + 1) % nodes.size()]});
    }

    int cnt = 0;
    cout << add.size() << "\n";
    for (int i=0; i<add.size(); i++) {
        cout << rm[i].first << " " << rm[i].second << " ";
        cout << add[i].first << " " << add[i].second << "\n";
    }

    return 0;
}