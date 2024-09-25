// https://codeforces.com/contest/1706/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

class UnionFind {
private:
    vector<int> p, wt;

public:
    UnionFind(int N)
    {
        p.assign(N, -1);
        wt.assign(N, 1e9);
    }
    int findSet(int i) { return (p[i] < 0) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j, int weight)
    {
        if (isSameSet(i, j)) return;
        int x = findSet(i), y = findSet(j);
        if (x > y) swap(x, y);
        p[x] += p[y], p[y] = x;
        wt[y] = weight;
    }

    // The maximum weight in the path from i to j
    int getWeight(int i, int j) {
        int w = 0;
        while (i != j) {
            if (wt[i] < wt[j]) w = wt[i], i = p[i];
            else w = wt[j], j = p[j];
        }
        return w;
    }
};

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return max(a, b);
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] += val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    int query(int node, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.assign(4 * sz, 0);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
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
        int n, m, q; cin >> n >> m >> q;

        UnionFind UF(n + 1);
        for (int i=1, u, v; i<=m; i++) {
            cin >> u >> v;
            if (UF.isSameSet(u, v)) continue;
            UF.unionSet(u, v, i);
        }

        SegmentTree st(n + 1);
        vector<int> weight(n + 1);
        for (int i=1; i<n; i++) {
            weight[i] = UF.getWeight(i, i + 1);
            st.update(i, weight[i]);
        }

        while (q--) {
            int l, r; cin >> l >> r;
            int ans = (l == r ? 0 : st.query(l, r - 1));
            cout << ans << " ";
        }
        cout << endl;
    }

    return 0;
}