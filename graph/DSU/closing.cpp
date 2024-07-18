// https://usaco.org/index.php?page=viewproblem2&cpid=646

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

int cnt = 0;
bool visited[200];
void dfs(int u, vector<vector<int>>& adj) {
    if (visited[u]) return;

    cnt++;
    visited[u] = 1;

    for (auto &v : adj[u]) {
        dfs(v, adj);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, adj);

    int base = 1;
    if (cnt < n) base = 0;

    vector<int> queries;
    int q = n;
    while (q--) {
        int u; cin >> u;
        queries.push_back(--u);
    }

    UnionFind UF(n);

    vector<int> ans;
    ans.push_back(base);
    for (int i=0; i<queries.size(); i++) {
        if (i == queries.size() - 2) {
            ans.push_back(1);
            break;
        }

        int u = queries[i];

        bool cc_increase = false;
        for (auto &v : adj[u]) {
            if (UF.isSameSet(u, v)) continue;
            UF.unionSet(u, v);
            cc_increase = true;
        }

        if (cc_increase) ans.push_back(UF.findSet(u));
        else ans.push_back(1);
    }

    // reverse(ans.begin(), ans.end());

    for (int i=0; i<ans.size(); i++) {
        int e = ans[i];
        cout << (e == 1 ? "YES\n" : "NO\n");
    }

    return 0;
}