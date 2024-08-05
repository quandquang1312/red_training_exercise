// https://vjudge.net/problem/UVA-10938
// Binary Lifting

#include <bits/stdc++.h>
using namespace std;

#define MAXN 5010

int timer, l;
int tin[MAXN], tout[MAXN], height[MAXN], parent[MAXN][15];
vector<int> adj[MAXN];

void dfs(int u, int p) {
    tin[u] = ++timer;
    parent[u][0] = p;

    for (auto &v : adj[u]) {
        if (v != p) {
            height[v] = height[u] + 1;
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

void preprocess(int n) {
    height[1] = 0, timer = 0, l = ceil(log2(n));

    for (int i=1; i<=n; i++) adj[i].clear();
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
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 1);

        for (int i=1; i<=l; i++)
            for (int u=1; u<=n; u++)
                parent[u][i] = parent[parent[u][i-1]][i-1];

        int q; cin >> q;
        while (q--) {
            int u, v;
            cin >> u >> v;
            if (height[u] > height[v]) swap(u, v);
            int d = dist(u, v);
            if (d % 2 == 0) {
                for (int i=1; i<=d/2; i++) v = parent[v][0];
                printf("The fleas meet at %d.\n", v);
            } else {
                if (height[u] == height[v]) for (int i=1; i<d/2; i++) u = parent[u][0], v = parent[v][0];
                else {
                    for (int i=1; i<=d/2; i++) {
                        v = parent[v][0];
                    }
                    u = parent[v][0];
                }

                if (u > v) swap(u, v);
                printf("The fleas jump forever between %d and %d.\n", u , v); 
            }
        }
    }

    return 0;
}