#include <bits/stdc++.h>
using namespace std;

#define MAXN 10010

class SegmentTree { // 1-based index sum segment tree
private:
    int n, tree[MAXN*4], lazy[MAXN*4];
    vector<int> arr;

    void build(int node, int tl, int tr) {
        if (tl == tr) tree[node] = arr[tl];
        else {
            int tm = (tl + tr) >> 1;
            build(node*2, tl, tm);
            build(node*2+1, tm+1, tr);
            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }

    int query(int node, int l, int r, int tl, int tr) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[node];
        push(node);
        int tm = (tl + tr) >> 1;
        return query(node*2, l, min(r, tm), tl, tm) + query(node*2+1, max(l, tm+1), r, tm+1, tr);
    }

    void push(int node) {
        if (lazy[node]) {
            tree[node*2] = tree[node*2+1] = tree[node];
            lazy[node*2] = lazy[node*2+1] = true;
            lazy[node] = false;
        }
    }

    void update(int node, int pos, int tl, int tr, int val) {
        if (tl == tr) tree[node] = val;
        else {
            int tm = (tl + tr) >> 1;

            if (pos <= tm) update(node*2, pos, tl, tm, val);
            else update(node*2+1, pos, tm+1, tr, val);

            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }

    void rangeUpdate(int node, int l, int r, int tl, int tr, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            tree[node] = val;
            lazy[node] = true;
        } else {
            push(node);
            int tm = (tl + tr) >> 1;
            rangeUpdate(node*2, l, min(r, tm), tl, tm, val);
            rangeUpdate(node*2+1, max(l, tm+1), r, tm+1, tr, val);
        }
    }

public:
    SegmentTree(int sz) {
        n = sz;
        arr.resize(n+5, 0);
    }

    int query(int l, int r) {
        return query(1, l, r, 1, n);
    }

    void update(int pos, int val) {
        update(1, pos, 1, n, val);
    }

    void rangeUpdate(int l, int r, int val) {
        rangeUpdate(1, l, r, 1, n, val);
    }
};

struct update_info {
    int l, r, x;
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    SegmentTree st(n+1);

    int l, r, x;
    vector<update_info> vect;
    for (int i=0; i<m; i++) {
        update_info info;
        cin >> info.l >> info.r >> info.x;
        vect.push_back(info);
    }

    for (int i=m-1; i>=0; i--) {
        int l = vect[i].l, r = vect[i].r, x = vect[i].x;

        if (l < x && r > x) {
            st.rangeUpdate(l, x-1, x);
            st.rangeUpdate(x+1, r, x);
        } else if (l == x) {
            st.rangeUpdate(l+1, r, x);
        } else if (r == x) {
            st.rangeUpdate(l, r-1, x);
        } else {
            st.rangeUpdate(l, r, x);
        }
    }

    for (int j=1; j<=n; j++) {
        cout << st.query(j,j) << " ";
    }
    cout << endl;

    return 0;
}