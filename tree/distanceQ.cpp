// https://cses.fi/problemset/task/1135

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX_N = 200005;

vector<pair<int, int>> tree[MAX_N];
int depth[MAX_N];
int dist[MAX_N];
int parent[MAX_N][20];

void dfs(int u, int p, int d, int d2) {
    depth[u] = d;
    dist[u] = d2;
    parent[u][0] = p;

    for (auto [v, w] : tree[u]) {
        if (v != p) {
            dfs(v, u, d + 1, d2 + w);
        }
    }
}

void buildSparseTable(int n) {
    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
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
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back({v, 1});
        tree[v].push_back({u, 1});
    }

    dfs(1, 0, 0, 0);
    buildSparseTable(n + 1);

    while (q--) {
        int u, v;
        cin >> u >> v;
        int ans = distance(u, v);
        cout << ans << '\n';
    }

    return 0;
}