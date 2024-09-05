// https://cses.fi/problemset/task/1190

#include <bits/stdc++.h>
using namespace std;

#define int long long

int max3(int a, int b, int c) {
    return max(max(a,b), max(b,c));
}

struct Node {
    int G, L, R, S;

    Node operator+(Node b) {
        return {
            max3(G, b.G, R + b.L),
            max(L, S + b.L),
            max(R + b.S, b.R),
            S + b.S
        };
    }
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;
    vector<int> arr;

    void build(int l, int r, int node) {
        if (l == r) {
            tree[node] = {max(0LL, arr[l]), max(0LL,  arr[l]), max(0LL,  arr[l]),  arr[l]};
        } else {
            int mid = (l + r) >> 1;
            build(l, mid, node * 2);
            build(mid + 1, r, node * 2 + 1);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] = {max(0LL, val), max(0LL, val), max(0LL, val), val};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);
            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }


public:
    SegmentTree(int sz, vector<int>& oarr) : n(sz) {
        tree.resize(4 * n);
        arr = oarr;
        build(1, n, 1);
    }

    int getMax() {
        return tree[1].G;
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
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

    vector<int> arr(n + 1);
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
    }

    SegmentTree st(n, arr);

    while (q--) {
        int x, y;
        cin >> x >> y;
        st.update(x, y);
        cout << st.getMax() << '\n';
    }

    return 0;
}