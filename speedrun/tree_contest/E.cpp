// https://codeforces.com/gym/102694/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> startIdx, endIdx;
int timer = 1;

void euler_tour(int at, int prev) {
    startIdx[at] = timer++;
    for (int n : adj[at]) {
        if (n != prev) { euler_tour(n, at); }
    }
    endIdx[at] = timer;
}

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return a * b;
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] = val;
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
        if (l > r) return 1;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        // Assign 1
        tree.assign(4 * n + 5, 1);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

vector<int> val;

int brute(int u, int prev) {
    int ans = val[u];
    for (auto &v : adj[u]) {
        if (v == prev) continue;
        ans = ans * brute(v, u);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    startIdx.assign(n * 2, 0);
    endIdx.assign(n * 2, 0);
    val.assign(n, 1);
    adj.resize(n);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler_tour(0, 0);

    SegmentTree st(n * 2 + 5);

    int q; cin >> q;
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            x--;
            st.update(startIdx[x], y);
            st.update(endIdx[x], -y);
            val[x] = y;
        } else { // t == 2
            x--, y--;
            int product_x = brute(x, x);
            int product_y = brute(y, y);
            // int product_x = st.query(startIdx[x], endIdx[x]);
            // int product_y = st.query(startIdx[y], endIdx[y]);
            double ans = (1.0 * product_x) / (1.0 * product_y);
            if (ans > 1000000000) printf("1000000000\n");
            else printf("%.6f\n", ans);
        }
    }

    return 0;
}