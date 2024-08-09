// https://atcoder.jp/contests/dp/tasks/dp_p

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int dp[100050][2];

int dfs(int u, int par, int c, vector<vector<int>>& adj) {
    if (dp[u][c] != -1) return dp[u][c];
    int ans = 1;
    if (c == 0) {
        for (auto &v : adj[u]) {
            if (v == par) continue;
            int ans_v = dfs(v, u, 1 - c, adj) % MOD;
            ans_v += dfs(v, u, c, adj) % MOD;
            ans_v %= MOD;
            ans *= ans_v;
            ans %= MOD;
        }
    } else {
        for (auto &v : adj[u]) {
            if (v == par) continue;
            int ans_v = dfs(v, u, 1 - c, adj) % MOD;
            ans *= ans_v;
            ans %= MOD;
        }
    }

    return dp[u][c] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    memset(dp, -1, sizeof dp);
    vector<vector<int>> adj(n+1);
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = ((dfs(1, 0, 0, adj) % MOD) + (dfs(1, 0, 1, adj) % MOD)) % MOD;
    cout << ans << '\n';

    return 0;
}