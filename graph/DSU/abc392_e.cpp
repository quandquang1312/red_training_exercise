// https://atcoder.jp/contests/abc392/tasks/abc392_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

// customized
class DSU {
private:
    vector<int> p, rank, setSize;
    vector<int> red;
    int numSets;

public:
    DSU(int n) {
        p.assign(n, 0);
        red.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        numSets = n;
    }

    void addRed(int i) {
        red[findSet(i)]++;
    }

    int getRed(int i) {
        return red[findSet(i)];
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

    vector<tuple<int, int, int>> redundant_edges;
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        if (dsu.isSameSet(u, v)) {
            dsu.addRed(u);
            redundant_edges.push_back({u, v, i + 1});
        } else {
            dsu.unionSet(u, v);
        }
    }

    vector<int> rootCC;
    for (int i=1; i<=n; i++) {
        if (dsu.findSet(i) == i) {
            rootCC.push_back(i);
        }
    }

    sort(rootCC.begin(), rootCC.end(), [&] (int u, int v) {
        int redU = dsu.getRed(u);
        int redV = dsu.getRed(v);

        return redU > redV;
    });

    map<int, vector<tuple<int, int, int>>> mp;
    for (auto &[u, v, idx] : redundant_edges) {
        int p = dsu.findSet(u);
        mp[p].push_back({u, v, idx});
    }

    int k = rootCC.size();
    cout << k - 1 << "\n";

    int j = 1;
    for (int i=0; ((i<k) && (j<k)); i++) {
        int p = rootCC[i];

        for (auto &[u, v, idx] : mp[p]) {
            if (j < k)
                cout << idx << " " << u << " " << rootCC[j++] << "\n";
            else break;
        }
    }

    return 0;
}