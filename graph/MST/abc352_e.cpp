// https://atcoder.jp/contests/abc352/tasks/abc352_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

class DSU {
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    DSU(int n) {
        p.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        numSets = n;
    }

    int findSet(int i) {
        if (p[i] == i) return i;
        return p[i] = findSet(p[i]);
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }

    int numOfSets() {
        return numSets;
    }

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;

        int x = findSet(i);
        int y = findSet(j);

        if (rank[x] > rank[y]) swap(x, y);

        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;

        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    DSU dsu(n + 1);

    vector<vector<int>> edges(m);

    for (int i=0; i<m; i++) {
        int k, w; cin >> k >> w;

        vector<int> st(k + 1);
        st[0] = w;

        for (int j=1; j<=k; j++) cin >> st[j];

        edges[i] = st;
    }

    sort(edges.begin(), edges.end(), [] (const vector<int> &v1, const vector<int> &v2) {
        return v1[0] < v2[0];
    });

    int prev = 0, mst = 0;
    for (auto &v : edges) {
        int w = v[0];
        prev = 0;
        for (int j=1; j<v.size(); j++) {
            int u = v[j];

            if (dsu.isSameSet(prev, u)) continue;

            if (prev != 0) {
                dsu.unionSet(prev, u);
                mst += w;
            }

            prev = u;
            if (dsu.sizeOfSet(prev) == n) break;
        }
    }

    if (dsu.sizeOfSet(prev) != n) mst = -1;
    cout << mst << "\n";

    return 0;
}