// https://codeforces.com/contest/339/problem/D

#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1 << 17) + 5;

bool xorFirst = false;

class SegmentTree { // 1-based index sum segment tree
private:
    int n, tree[MAXN*4], lazy[MAXN*4];
    vector<int> arr;

    void build(int node, int tl, int tr, int depth) {
        if (tl == tr) {
            tree[node] = arr[tl];
            // printf("[build] %d: %d->%d\n", node, tl, arr[tl]);
        }
        else {
            int tm = (tl + tr) >> 1;
            build(node*2, tl, tm, depth + 1);
            build(node*2+1, tm+1, tr, depth + 1);
            if (xorFirst) {
                if (depth % 2 == 0) tree[node] = tree[node*2] ^ tree[node*2+1];
                else tree[node] = tree[node*2] | tree[node*2+1];
            } else {
                if (depth % 2 == 0) tree[node] = tree[node*2] | tree[node*2+1];
                else tree[node] = tree[node*2] ^ tree[node*2+1];
            }
        }
    }

    int query(int node, int l, int r, int tl, int tr, int depth) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[node];
        int tm = (tl + tr) >> 1;

        int le = query(node*2, l, min(r, tm), tl, tm, depth+1);
        int ri = query(node*2+1, max(l, tm+1), r, tm+1, tr, depth+1);
        if (xorFirst) {
            if (depth % 2 == 0) return le ^ ri;
            else return le | ri;
        } else {
            if (depth % 2 == 0) return le | ri;
            else return le ^ ri;
        }
    }

    void update(int node, int pos, int tl, int tr, int val, int depth) {
        if (tl == tr) tree[node] = val;
        else {
            int tm = (tl + tr) >> 1;

            if (pos <= tm) update(node*2, pos, tl, tm, val, depth+1);
            else update(node*2+1, pos, tm+1, tr, val, depth+1);

           if (xorFirst) {
                if (depth % 2 == 0) tree[node] = tree[node*2] ^ tree[node*2+1];
                else tree[node] = tree[node*2] | tree[node*2+1]; 
           } else {
                if (depth % 2 == 0) tree[node] = tree[node*2] | tree[node*2+1];
                else tree[node] = tree[node*2] ^ tree[node*2+1]; 
           }
        }
    }

public:
    SegmentTree(vector<int> vect) {
        arr = vect;
        n = vect.size() - 1;

        // printf("arr.size() : %d, n: %d\n", vect.size(), n);

        build(1, 1, n, 0);
    }

    int query(int l, int r) {
        return query(1, l, r, 1, n, 0);
    }

    void update(int pos, int val) {
        update(1, pos, 1, n, val, 0);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    xorFirst = (n % 2 == 0);
    n = (1 << n);

    vector<int> arr(n+1);
    for (int i=1; i <= n; i++) {
        cin >> arr[i];
    }

    SegmentTree st(arr);

    for (int i=0; i<m; i++) {
        int p, b; cin >> p >> b;
        st.update(p, b);
        int ans = st.query(1, n);
        cout << ans << endl;
    }

    return 0;
}