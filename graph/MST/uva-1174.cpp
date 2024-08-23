// https://vjudge.net/problem/UVA-1174

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        unordered_map<string, int> idx;
        vector<tuple<int, int, int>> EL;
        vector<bool> visited(n + 1, false);

        int timer = 0;
        for (int i=0, w; i<m; i++) {
            string u, v;
            cin >> u >> v >> w;
            if (idx.find(u) == idx.end()) idx[u] = timer++;
            if (idx.find(v) == idx.end()) idx[v] = timer++;
            EL.push_back({w, idx[u], idx[v]});
        }

        sort(EL.begin(), EL.end());

        int mst = 0, cnt = 0;
        UnionFind UF(n + 1);

        for (auto &[w, u, v] : EL) {
            if (UF.isSameSet(u, v)) continue;
            UF.unionSet(u, v);
            mst += w;
            cnt++;

            if (cnt == n-1) break;
        }

        printf("%d\n", mst);
        if (tc) printf("\n");

    }

    return 0;
}