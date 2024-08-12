// https://atcoder.jp/contests/dp/tasks/dp_v

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100100

int64_t m = 1e9 + 7;
int64_t f[MAXN], g[MAXN];

void dfs(int u, int par, vector<vector<int>>& adj) {
    f[u] = 1LL;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u, adj);
        f[u] = (f[u] * f[v]) % m;
    }

    f[u] = (f[u] + 1LL) % m;
}

void rerooting(int u, int par, vector<vector<int>>& adj) {
    vector<int> child;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        child.push_back(v);
    }

    vector<int64_t> pref(child.size() + 5, 1LL), suff(child.size() + 5, 1LL);
    for (int i=1; i<=child.size(); i++) pref[i] = (pref[i - 1] * f[child[i - 1]]) % m;
    for (int i=child.size(); i>=1; i--) suff[i] = (suff[i + 1] * f[child[i - 1]]) % m;

    for (int i=0; i<child.size(); i++) {
        g[child[i]] = (g[u] * pref[i]) % m;
        g[child[i]] = (g[child[i]] * suff[i + 2]) % m;
        g[child[i]] = (g[child[i]] + 1LL) % m;
    }

    for (auto &v : child) rerooting(v, u, adj);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1, adj);
    g[1] = 1LL;
    rerooting(1, 1, adj);
    for (int i=1; i<=n; i++) {
        // cout << i << ": " << f[i] << "-" << g[i] << "\n";
        cout << ((f[i] - 1LL + m) * g[i]) % m << '\n';
    };

    return 0;
}