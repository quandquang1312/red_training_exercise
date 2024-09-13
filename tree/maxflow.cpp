// https://usaco.org/index.php?page=viewproblem2&cpid=576

#include <bits/stdc++.h>
using namespace std;

#define MAXN 60100

vector<vector<int>> adj;
vector<int> S, E, ans;
int n, q;

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

int dfs(int u, int par) {
    int sm = 0;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        sm += dfs(v, u);
    }

    // for every twos of path go through u as LCA
    // we count only one, so E[u]/2
    ans[u] = sm + S[u] - E[u]/2;

    // since every pair of children nodes go through u as the LCA we S[a]++, S[b]++,
    // then we have to eliminate all of the children nodes
    return sm + S[u] - E[u];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #else
        freopen("maxflow.in", "r", stdin);
        freopen("maxflow.out", "w", stdout);
    #endif

    cin >> n >> q;

    adj.resize(n + 1);
    S.assign(n + 1, 0);
    E.assign(n + 1, 0);
    ans.assign(n + 1, 0);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LCA mLCA(adj, 1);

    while (q--) {
        int u, v;
        cin >> u >> v;
        
        int w = mLCA.lca(u, v);

        S[u]++, S[v]++, E[w] += 2;
    }

    dfs(1, 0);

    int rs = 0;
    for (int i=1; i<=n; i++) {
        rs = max(rs, ans[i]);
    }

    cout << rs << '\n';

    return 0;
}