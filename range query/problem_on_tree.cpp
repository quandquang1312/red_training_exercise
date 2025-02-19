// https://codeforces.com/contest/276/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree { // 0-based index segment tree with lazy update
private:
    int n;
    vector<int> tree, lazy, arr;

    void build(int node, int tl, int tr) {
        if (tl == tr) tree[node] = arr[tl];
        else {
            int tm = (tl + tr) >> 1;
            build(node*2+1, tl, tm);
            build(node*2+2, tm+1, tr);
            tree[node] = merge(tree[node*2+1], tree[node*2+2]);
        }
    }

    int merge(int a, int b) {
        return a + b; // sum segment tree
    }

    int query(int node, int l, int r, int tl, int tr) {
        if (l > r) return 0;
        push(node, tl, tr); 
        if (l == tl && r == tr) return tree[node];
        int tm = (tl + tr) >> 1;
        return merge(query(node*2+1, l, min(r, tm), tl, tm),
                    query(node*2+2, max(l, tm+1), r, tm+1, tr));
    }

    void push(int node, int tl, int tr) {
        if (lazy[node]) {
            tree[node] += lazy[node] * (tr - tl + 1);
            if (tl != tr) {
                lazy[node*2+1] += lazy[node];
                lazy[node*2+2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int pos, int tl, int tr, int val) {
        if (tl == tr) tree[node] += val;
        else {
            int tm = (tl + tr) >> 1;
            push(node, tl, tr);
            if (pos <= tm) update(node*2+1, pos, tl, tm, val);
            else update(node*2+2, pos, tm+1, tr, val);
            tree[node] = merge(tree[node*2+1], tree[node*2+2]);
        }
    }

    void rangeUpdate(int node, int l, int r, int tl, int tr, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[node] += val;
            push(node, tl, tr);
        } else {
            int tm = (tl + tr) >> 1;
            push(node, tl, tr);
            rangeUpdate(node*2+1, l, min(r, tm), tl, tm, val);
            rangeUpdate(node*2+2, max(l, tm+1), r, tm+1, tr, val);
            tree[node] = merge(tree[node*2+1], tree[node*2+2]);
        }
    }

public:
    SegmentTree(int sz) {
        n = sz;
        arr.resize(n, 0);
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    int query(int l, int r) {
        return query(0, l, r, 0, n-1);
    }

    void update(int pos, int val) {
        update(0, pos, 0, n-1, val);
    }

    void rangeUpdate(int l, int r, int val) {
        rangeUpdate(0, l, r, 0, n-1, val);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> chains;
    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, 0);
    vector<int> chain_idx(n + 1, -1);

    function<void(int, int, int, vector<int>&)> dfs = [&] (int u, int d, int p, vector<int>& c) -> void {
        depth[u] = d;

        for (auto &v : adj[u]) {
            if (v == p) continue;

            c.push_back(v);
            dfs(v, d + 1, u, c);
            c.pop_back();
        }

        if (u != 1 && adj[u].size() == 1) { // leaf node
            chains.push_back(c);
        }

        chain_idx[u] = chains.size() - 1;
    };

    vector<int> c;
    dfs(1, 0, 0, c);

    vector<SegmentTree> Sts(chains.size(), SegmentTree(n + 1));

    int rt_value = 0;

    int tp, v, x, d;
    while (q--) {
        cin >> tp;
        if (tp == 0) {
            cin >> v >> x >> d;

            if (v == 1) {
                rt_value += x;
                for (int i=0; i<chains.size(); i++) {
                    Sts[i].rangeUpdate(0, d - 1, x);
                }

                continue;
            }

            int idx = chain_idx[v];

            if (depth[v] - d >= 0) { 
                // cout << "update only in its chain: " << v << "(" << idx << ")" << " - " << d << "\n";
                int lo = max(0LL, depth[v] - d - 1);
                int hi = min((int) chains[idx].size(), depth[v] + d - 1);

                // cout << "update: " << idx << ": " << lo << "->" << hi << "\n";
                Sts[idx].rangeUpdate(lo, hi, x);
                // cout << "query: " << idx << ": " << depth[v] - 1 << "\n";

                if (depth[v] - d == 0) {
                    rt_value += x; 
                    // cout << " update root\n";
                }
            } else {
                rt_value += x; // update root
                // cout << "update other also: " << v << " - " << d << "\n";

                int rm = d - depth[v];

                for (int i=0; i<chains.size(); i++) {
                    int hi = max(0LL, rm - 1 - 1);
                    if (i == idx) hi = min((int) chains[idx].size(), depth[v] + d - 1);

                    // cout << "update: " << i << " -> " << hi << "\n"; 
                    Sts[i].rangeUpdate(0, hi, x);
                }
            }
        } else if (tp == 1) {
            cin >> v;
            if (v == 1) cout << rt_value << "\n";
            else {
                int idx = chain_idx[v];
                int ans = Sts[idx].query(depth[v] - 1, depth[v] - 1);
                cout << ans << "\n";
            }
        }
    }

    return 0;
}