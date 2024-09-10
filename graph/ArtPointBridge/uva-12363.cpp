// https://vjudge.net/problem/UVA-12363

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dfs_num, dfs_low, parent;
vector<pair<int, int>> bridges;
int timer;

#define UNVISITED -1

class UnionFind {
private:
    vector<int> p, rank;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
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
    }
};

void dfs(int u)
{
    dfs_num[u] = dfs_low[u] = timer++;

    for (auto v : adj[u])
    {
        if (dfs_num[v] == UNVISITED) {
            parent[v] = u;

            dfs(v);

            if (dfs_low[v] > dfs_num[u]) bridges.push_back({u, v});

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void preprocess(int n) {
    timer = 0;
    adj.clear();
    adj.resize(n + 1);
    parent.assign(n + 1, -1);
    dfs_low.assign(n + 1, 0);
    dfs_num.assign(n + 1, UNVISITED);
    bridges.clear();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, q;
    while (cin >> n >> m >> q) {
        if (n + m + q == 0) break;

        preprocess(n);

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i=1; i<=n; i++) {
            if (dfs_num[i] == UNVISITED)
                dfs(i);
        }

        UnionFind UF(n + 1);
        for (auto &e : bridges) {
            if (UF.isSameSet(e.first, e.second)) continue;

            UF.unionSet(e.first, e.second);
        }

        while (q--) {
            int u, v;
            cin >> u >> v;
            
            if (UF.isSameSet(u, v)) cout << "Y\n";
            else cout << "N\n";
        }

        cout << "-\n";
    }

    return 0;
}