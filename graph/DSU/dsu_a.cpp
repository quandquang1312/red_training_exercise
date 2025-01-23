// https://oj.vnoi.info/problem/dsu_a

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
    for (int i=0, u, v; i<m; i++) {
        string tp; cin >> tp;
        if (tp == "union") {
            cin >> u >> v;
            dsu.unionSet(u, v);
        } else {
            cin >> u >> v;
            string ans = (dsu.isSameSet(u, v) ? "YES" : "NO");
            cout << ans << "\n";
        }
    }

    return 0;
}