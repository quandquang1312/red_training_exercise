// https://codeforces.com/contest/1187/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200100

vector<vector<int>> adj;
vector<int> sz, dp;
int ans;

void calcSize(int u, int par) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        calcSize(v, u);
        sz[u] += sz[v];
    }
}

void dfs(int u, int par) {
    dp[u] = sz[u];

    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        dp[u] += dp[v];
    }
}

void rerooting(int u, int par) {
    ans = max(ans, dp[u]);

    for (auto &v : adj[u]) {
        if (v == par) continue;

        // detach v from u
        dp[u] -= dp[v];
        dp[u] -= sz[v];
        sz[u] -= sz[v];

        // attach u to v, now u considered as a child of v
        dp[v] += dp[u];
        dp[v] += sz[u];
        sz[v] += sz[u];

        rerooting(v, u);

        // bakctrack
        sz[v] -= sz[u];
        dp[v] -= sz[u];
        dp[v] -= dp[u];

        dp[u] += dp[v];
        dp[u] += sz[v];
        sz[u] += sz[v];
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

    adj.resize(n + 1);
    sz.resize(n + 1, 0), dp.resize(n + 1, 0);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // brute force
    // for (int r=1; r<=n; r++) {
    //     sz.assign(n + 1, 0), dp.assign(n + 1, 0);
    //     calcSize(r, r);
    //     dfs(r, r);
    //     for (int i=1; i<=n; i++) {
    //         cout << i << ": " << sz[i] << " - " << dp[i] << '\n'; 
    //     }
    // }

    // rerooting
    calcSize(1, 1);
    dfs(1, 1);
    rerooting(1, 1);
    cout << ans << '\n';

    return 0;
}