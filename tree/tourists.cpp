// https://open.kattis.com/problems/tourists?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 2 * 1e5 + 10;

int timer, l;
int tin[MAXN], tout[MAXN], height[MAXN], parent[MAXN][20];
vector<vector<int>> adj; // [MAXN];

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
    if (is_ancestor(v, u)) return v;

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
    height[1] = 0, timer = 0, l = ceil(log2(n + 1));

    adj.resize(n+1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    preprocess(n);

    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1);

    // Calculate sparse table
    for (int u=0; u<=n; u++)
        for (int i=1; i<=l; i++)
            parent[u][i] = parent[parent[u][i-1]][i-1];

    int ans = 0;
    for (int i=1; i<=n; i++) {
        for (int j=i*2; j<=n; j+=i) {
            ans += dist(i, j) + 1; 
        }
    }

    cout << ans << '\n';

    return 0;
}