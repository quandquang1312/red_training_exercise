// https://cses.fi/problemset/task/1132
// TLE edition

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010

int f[MAXN], g[MAXN];
int ans;

void dfs(int u, int par, vector<vector<int>>& adj) {
    f[u] = 0;

    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u, adj);
        f[u] = max(f[u], f[v] + 1);
    }
}

void rerooting(int u, int par, vector<vector<int>>& adj) {
    g[u] = f[u];
    int n = adj[u].size();

    vector<int> pref_max(n + 5, 0), suff_max(n + 5, 0);
    for (int i=0; i<n; i++) {
        pref_max[i + 1] = max(f[adj[u][i]] + 1, pref_max[i]);
    }

    for (int i=n-1; i>=0; i--) {
        suff_max[i] = max(f[adj[u][i]] + 1, suff_max[i + 1]);
    }

    for (int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == par) continue;

        // detach v from u and attach u to v
        int original_fu = f[u], original_fv = f[v];
        
        // brute force
        // f[u] = 0;
        // for (auto w : adj[u]) {
        //     if (v == w) continue;
        //     f[u] = max(f[u], f[w] + 1);
        // }

        if (i == 0) { f[u] = suff_max[i + 1]; }
        if (i == n -1) { f[u] = pref_max[i]; }
        else f[u] = max(pref_max[i], suff_max[i + 1]);

        f[v] = max(f[v], f[u] + 1);

        rerooting(v, u, adj);

        // backtrack
        f[v] = original_fv;
        f[u] = original_fu;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for (int i=0, u, v; i<n - 1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // brute force
    // for (int i=1; i<=n; i++) {
    //     memset(f, 0, sizeof f);
    //     dfs(i, i, adj);
    //     cout << i << ": " << f[i] << "\n";
    // } cout << endl;

    // rerooting
    dfs(1, 1, adj);
    rerooting(1, 0, adj);
    g[1] = f[1];
    for (int i=1; i<=n; i++) {
        cout << g[i] << '\n';
    }

    return 0;
}