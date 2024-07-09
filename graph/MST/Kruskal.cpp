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

void kruskal()
{
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> adj(m);

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[i] = {u, v, w};
    }

    sort(adj.begin(), adj.end());

    int mst_cost = 0, num_taken = 0;
    UnionFind UF(n);
    for (auto &[u, v, w] : adj)
    {
        if (UF.isSameSet(u, v)) continue;

        mst_cost += w;
        UF.unionSet(u, v);
        num_taken++;

        if (num_taken == n - 1) break;
    }

    cout << mst_cost << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    kruskal();

    return 0;
}