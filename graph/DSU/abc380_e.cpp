// https://atcoder.jp/contests/abc380/tasks/abc380_e

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
        p[y] = x, setSize[x] += setSize[y];
        setSize[y] = 0;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, q; cin >> n >> q;

    UnionFind UF(n + 2);

    vector<int> cnt(n + 2, 1);
    cnt[0] = 0;
    vector<int> color(n + 2), L(n + 2), R(n + 2);
    for (int i=1; i<=n; i++) {
        color[i] = i;
        L[i] = i;
        R[i] = i;
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, c; cin >> x >> c;
            int root = UF.findSet(x);

            if (color[root] == c) continue;

            int sz = UF.sizeOfSet(root);

            int l = L[root], r = R[root];

            cnt[color[root]] -= sz;
            color[root] = c;
            cnt[c] += sz;

            if (color[UF.findSet(l - 1)] == c) { // the root has the same color with the previous cell
                L[root] = L[UF.findSet(l - 1)];
                UF.unionSet(root, l - 1);
            }
            if (color[UF.findSet(r + 1)] == c) { // the root has the same color with the next region cell
                R[root] = R[UF.findSet(r + 1)];
                UF.unionSet(root, r + 1);
            }
        } else { // t == 2
            int c; cin >> c;
            cout << cnt[c] << "\n";
        }
    }

    return 0;
}