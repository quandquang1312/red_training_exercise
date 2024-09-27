// https://codejam.lge.com/problem/18769

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

    int tc; cin >> tc;
    while (tc--) {
        int r, c; cin >> r >> c;
        int n = r * c;

        vector<vector<int>> adj(n + 1);
        vector<tuple<int, int, int>> Edges;
        for (int i=0; i<r; i++) {
            for (int j=1, w; j<=c-1; j++) {
                cin >> w;
                int u = (i * c) + j;
                Edges.push_back({w, u, u + 1});
                Edges.push_back({w, u + 1, u});
            }
        }

        for (int i=0; i<r-1; i++) {
            for (int j=1, w; j<=c; j++) {
                cin >> w;
                int u = (i * c) + j;
                Edges.push_back({w, u, u + c});
                Edges.push_back({w, u + c, u});
            }
        }

        sort(Edges.begin(), Edges.end());

        // for (auto &[w, u, v] : Edges) {
        //     cout << u << " - " << v << ": " << w << "\n";
        // }

        UnionFind UF(n + 1);
        int mst = 0, cnt = 0;
        for (auto &[w, u, v] : Edges) {
            if (UF.isSameSet(u, v)) continue;
            UF.unionSet(u, v);

            mst += w;
            cnt++;

            if (cnt == n -1) break;
        }

        cout << mst << endl;
    }

    return 0;
}