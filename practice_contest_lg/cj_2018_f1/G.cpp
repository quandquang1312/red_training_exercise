// https://codejam.lge.com/problem/16202

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

    sort(Edges.begin(), Edges.end());

    UnionFind UF(n + 1);

    int mst = 0, cnt = 0;
    vector<tuple<int, int, int>> paths;
    for (auto &[w, u, v] : Edges) {
        if (UF.isSameSet(u, v)) continue;
        mst += w;
        UF.unionSet(u, v);
        paths.push_back({w, u, v});
        cnt++;

        if (cnt == n - 1) break;
    }

    sort(paths.begin(), paths.end());

    for (auto &[w, u, v] : paths) {
        cout << u << " - " << v << ": " << w << "\n";
    }

    cout << mst << endl;

    return 0;
}