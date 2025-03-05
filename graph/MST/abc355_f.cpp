// https://atcoder.jp/contests/abc355/tasks/abc355_f

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

    int n, q; cin >> n >> q;

    int ans = 0;
    vector<DSU> dsu(10, DSU(n + 1));
    for (int i=1, u, v, w; i<n; i++) {
        cin >> u >> v >> w;
        for (int j=w; j<10; j++) {
            if (!dsu[j].isSameSet(u, v)) {
                dsu[j].unionSet(u, v);
            } else break;
        }

        ans += w;
    }

    for (int i=0, u, v, w; i<q; i++) {
        cin >> u >> v >> w;
        for (int j=w; j<10; j++) {
            if (!dsu[j].isSameSet(u, v)) {
                dsu[j].unionSet(u, v);
                ans--;
            } else break;
        }

        cout << ans << "\n";
    }

    return 0;
}