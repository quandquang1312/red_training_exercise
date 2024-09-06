// https://judge.yosupo.jp/problem/point_set_range_composite

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

class SegmentTree {
private:
    int n;
    vector<pair<int, int>> tree;

    pair<int, int> merge(pair<int, int> fa, pair<int, int> fb) {
        swap(fa, fb);
        return {{(fa.first * fb.first) % MOD}, {(fa.first * fb.second + fa.second) % MOD}};
    }

    void update(int node, int tl, int tr, int pos, pair<int, int> val) {
        if (tl == tr) {
            tree[node] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);

            pair<int, int> fa = tree[node * 2], fb = tree[node * 2 + 1];
            tree[node] = merge(fa, fb);
        }
    }

    pair<int, int> query(int node, int tl, int tr, int l, int r) {
        if (l > r) return {1, 0};
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        pair<int, int> fa = query(node*2, tl, tm, l, min(r, tm));
        pair<int, int> fb = query(node*2+1, tm+1, tr, max(l, tm+1), r);
        return merge(fa, fb);
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.resize(4 * (n + 1) + 10);
    }

    void update(int pos, int a, int b) {
        update(1, 1, n, pos, {a, b});
    }

    pair<int, int> query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    SegmentTree st(n);
    for (int i=1, a, b; i<=n; i++) {
        cin >> a >> b;
        st.update(i, a, b);
    }

    while (q--) {
        int tp; cin >> tp;
        if (tp == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            p++;
            st.update(p, c, d);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l++;
            pair<int, int> ans = st.query(l, r);
            cout << (ans.first * x + ans.second) % MOD << '\n';
        }
    }


    return 0;
}