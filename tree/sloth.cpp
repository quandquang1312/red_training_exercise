// https://codeforces.com/gym/102694/problem/C

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 300010
#define LOG 23

vector<vector<int>> adj;
int depth[MAX_N], dist[MAX_N];
int parent[MAX_N][LOG];

void dfs(int u, int p, int d, int d2) {
    depth[u] = d;
    dist[u] = d2;
    parent[u][0] = p;

    for (auto &v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1, d2 + 1);
        }
    }
}

void buildSparseTable(int n) {
    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
}

int query(int u, int k) {
    for (int i=0; i<LOG; i++) {
        if (k & (1 << i)) {
            u = parent[u][i];
            if (u == -1) break;
        }
    }

    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int log = 1;
    while ((1 << log) <= depth[u]) log++;
    --log;

    for (int i = log; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (int i = log; i >= 0; --i) {
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int distance(int u, int v) {
    int l = lca(u, v);
    return dist[u] + dist[v] - (2 * dist[l]);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n;

    adj.resize(n + 1);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, 0, 0);
    buildSparseTable(n);

    cin >> q;
    while (q--) {
        int u, v, c;
        cin >> u >> v >> c;

        int d = distance(u, v);
        if (d <= c) {
            cout << v << '\n';
        } else {
            int w = lca(u, v);
            int duw = distance(u, w);
            int dvw = distance(v, w);

            int ans;

            if (duw >= c) {
                ans = query(u, c);
            } else {
                ans = query(v, dvw - (c - duw));
            }

            cout << ans << '\n';
        }
    }

    return 0;
}