// https://acm.timus.ru/problem.aspx?space=1&num=1471
// LCA RMQ Sparse Table
// Binary Lifting

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50005;

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

    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    dfs(0, -1, 0, 0);
    buildSparseTable(n);

    int m;
    cin >> m;

    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << distance(u, v) << "\n";
    }

    return 0;
}
