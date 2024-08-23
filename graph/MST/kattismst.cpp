// https://open.kattis.com/problems/minspantree

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

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 & m == 0) break;

        vector<tuple<int, int, int>> EL;
        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            EL.push_back({w, u, v});
        }

        sort(EL.begin(), EL.end());

        UnionFind UF(n + 1);
        int mst = 0, cnt = 0;

        vector<pair<int, int>> sol;
        for (auto [w, u, v] : EL) {
            if (UF.isSameSet(u, v)) continue;
            mst += w;
            cnt++;

            UF.unionSet(u, v);
            if (u > v) swap(u, v);
            sol.push_back({u, v});

            if (cnt == n-1) break;
        }

        if (cnt != n - 1) {
            cout << "Impossible\n";
        } else {
            cout << mst << '\n';

            sort(sol.begin(), sol.end());
            for (auto &[u, v] : sol) {
                cout << u << " " << v << '\n';
            }
        }
    }

    return 0;
}