// https://usaco.org/index.php?page=viewproblem2&cpid=921

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return a ^ b;
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
        if (l > r) return 0;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz + 10) {
        tree.assign(4 * n, 0);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

vector<vector<int>> adj;
vector<int> startIdx, endIdx;
int timer = 1;

void euler_tour(int at, int prev) {
    startIdx[at] = timer++;
    for (int n : adj[at]) {
        if (n != prev) { euler_tour(n, at); }
    }
    endIdx[at] = timer++;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #else 
        freopen("cowland.in", "r", stdin);
        freopen("cowland.out", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1);
    adj.resize(n + 1);
    startIdx.resize(n + 1);
    endIdx.resize(n + 1);

    for (int i=1; i<=n; i++) cin >> arr[i];
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler_tour(1, 0);

    SegmentTree st(n * 2 + 10);
    for (int i=1; i<=n; i++) {
        st.update(startIdx[i], arr[i]);
        st.update(endIdx[i], arr[i]);
    }

    LCA mLCA(adj, 1);

    while (q--) {
        int type, i, j;
        cin >> type >> i >> j;
        if (type == 2) {
            int l = mLCA.lca(i, j), ans;
            if (l != i && l != j) {
                int x = st.query(min(startIdx[l], startIdx[i]), max(startIdx[l], startIdx[i]));
                int y = st.query(min(startIdx[l], startIdx[j]), max(startIdx[l], startIdx[j]));
                ans = x ^ y ^ arr[l];
            } else {
                if (startIdx[i] > startIdx[j]) swap(i, j);
                ans = st.query(startIdx[i], startIdx[j]);
            }

            cout << ans << '\n';
        } else { // edit
            arr[i] = j;
            st.update(startIdx[i], arr[i]);
            st.update(endIdx[i], arr[i]);
        }
    }

    return 0;
}