#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 500010;

class SegmentTree { // 1-based index sum segment tree
private:
    int n;
    int tree[MAXN*4], lazy[MAXN*4];
    vector<int> arr;

    void build(int node, int tl, int tr) {
        if (tl == tr) {
            tree[node] = arr[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build(node<<1, tl, tm);
            build(node<<1|1, tm+1, tr);
            tree[node] = tree[node<<1] + tree[node<<1|1];
        }
    }

    void push(int node, int tl, int tr) {
        if (lazy[node] != 0) {
            int tm = (tl + tr) >> 1;
            tree[node<<1] += lazy[node] * (tm - tl + 1);
            lazy[node<<1] += lazy[node];
            tree[node<<1|1] += lazy[node] * (tr - tm);
            lazy[node<<1|1] += lazy[node];
            lazy[node] = 0;
        }
    }

    int query(int node, int l, int r, int tl, int tr) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[node];
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        return query(node<<1, l, min(r, tm), tl, tm) + query(node<<1|1, max(l, tm+1), r, tm+1, tr);
    }

    void update(int node, int pos, int tl, int tr, int val) {
        if (tl == tr) {
            tree[node] += val;
        } else {
            push(node, tl, tr);
            int tm = (tl + tr) >> 1;
            if (pos <= tm)
                update(node<<1, pos, tl, tm, val);
            else
                update(node<<1|1, pos, tm+1, tr, val);
            tree[node] = tree[node<<1] + tree[node<<1|1];
        }
    }

    void rangeUpdate(int node, int l, int r, int tl, int tr, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            tree[node] += val * (tr - tl + 1);
            lazy[node] += val;
        } else {
            push(node, tl, tr);
            int tm = (tl + tr) >> 1;
            rangeUpdate(node<<1, l, min(r, tm), tl, tm, val);
            rangeUpdate(node<<1|1, max(l, tm+1), r, tm+1, tr, val);
            tree[node] = tree[node<<1] + tree[node<<1|1];
        }
    }

public:
    SegmentTree(int sz) {
        n = sz;
        arr.resize(n + 5, 0);
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
    }

    int query(int l, int r) {
        return query(1, l, r, 1, n);
    }

    void update(int pos, int val) {
        update(1, pos, 1, n, val);
    }

    void rangeUpdate(int l, int r, int val) {
        if (l > r) return;
        rangeUpdate(1, l, min(n, r), 1, n, val);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n + 1);

    SegmentTree st(n + 5);

    for (int i=1; i<=n; i++) {
        cin >> arr[i];
        st.update(i, arr[i]);
    }

    vector<int> ans(n + 1, 0);
    for (int i=1; i<=n; i++) {
        int val = st.query(i, i);
        if (val == 0) continue;
        int use = min(n, i + val) - (i + 1) + 1;
        st.rangeUpdate(i + 1, i + use, 1);
        // cout << i << ": " << val << " - " << use << "\n";
        ans[i] = val - use;
    }

    for (int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    } cout << "\n";

    return 0;
}