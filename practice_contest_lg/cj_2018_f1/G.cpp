// https://codejam.lge.com/problem/16202

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

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

int kruskal(int n, const vector<tuple<int, int, int>>& Edges, vector<bool>& removed, int& rm) {
    int mst = 0, cnt = 0;
    rm = INF;

    UnionFind UF(n + 1);
    for (auto &[w, u, v] : Edges) {
        if (removed[w]) continue;
        if (UF.isSameSet(u, v)) continue;

        mst += w;
        UF.unionSet(u, v);
        rm = min(rm, w);
        cnt++;

        if (cnt == n - 1) break;
    }

    return (cnt == n - 1 ? mst : 0);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<tuple<int, int, int>> Edges;
    for (int w=1, u, v; w<=m; w++) {
        cin >> u >> v;
        Edges.push_back({w, u, v});
    }

    vector<bool> removed(m + 1, false);

    int rm = -1;
    for (int i=0; i<k; i++) {
        int mst = kruskal(n, Edges, removed, rm);
        cout << mst << " ";
        removed[rm] = true;
    }

    return 0;
}