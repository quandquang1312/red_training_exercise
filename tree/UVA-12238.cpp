// https://vjudge.net/problem/UVA-12238
// Binary Lifting LCA, Weighted

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e5 + 10;

int timer, l;
int tin[MAXN], tout[MAXN], height[MAXN], parent[MAXN][18], len[MAXN];
vector<pair<int, int>> adj[MAXN];

void dfs(int u, int p) {
    tin[u] = ++timer;
    parent[u][0] = p;

    for (auto &[v, w] : adj[u]) {
        if (v != p) {
            height[v] = height[u] + 1;
            len[v] = len[u] + w;
            dfs(v, u);
        }
    }

    tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;

    for (int i=l; i>=0; i--)
        if (!is_ancestor(parent[u][i], v))
            u = parent[u][i];

    return parent[u][0];
}

int dist(int u, int v) {
    int lc = lca(u, v);
    return height[u] + height[v] - 2 * height[lc];
}

int distLen(int u, int v) {
    int lc = lca(u, v);
    return len[u] + len[v] - 2 * len[lc];
}

void preprocess(int n) {
    len[0] = 0, height[0] = 0, timer = 0, l = ceil(log2(n));

    for (int i=0; i<n; i++) adj[i].clear();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n;
    while (cin >> n) {
        if (n == 0) break;

        preprocess(n);

        for (int i=1; i<n; i++) {
            int u, w; cin >> u >> w;
            adj[u].push_back({i, w});
            adj[i].push_back({u, w});
        }

        dfs(0, 0);

        for (int u=0; u<n; u++)
            for (int i=1; i<=l; i++)
                parent[u][i] = parent[parent[u][i-1]][i-1];

        int q; cin >> q;
        while (q--) {
            int u, v;
            cin >> u >> v;
            int d = distLen(u, v);

            cout << d;
            if (q) cout << " ";
        }
        cout << '\n';
    }

    return 0;
}