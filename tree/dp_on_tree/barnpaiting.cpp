// https://atcoder.jp/contests/dp/tasks/dp_p

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int dp[100050][3];
int painted[100050];

int dfs(int u, int par, int c, vector<vector<int>>& adj) {
    if (painted[u] != -1 && c != painted[u]) return dp[u][c] = 0;
    if (dp[u][c] != -1) return dp[u][c];
    int ans = 1;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        if (painted[v] == c) return dp[u][c] = 0;
        int ans_v = 0;
        for (int i = 0; i < 3; i++) {
            if (i == c) continue;
            ans_v += dfs(v, u, i, adj) % MOD;
            ans_v %= MOD;
        }
        ans *= ans_v;
        ans %= MOD;
    }

    return dp[u][c] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #if 1
        freopen("barnpainting.in", "r", stdin);
        freopen("barnpainting.out", "w", stdout);
    #endif

    int n, k; cin >> n >> k;
    memset(dp, -1, sizeof dp);
    memset(painted, -1, sizeof painted);
    vector<vector<int>> adj(n+1);
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int st = 1;
    for (int i=0, u, c; i<k; i++) {
        cin >> u >> c;
        painted[u] = c - 1;
        st = u;
    }

    int ans = dfs(st, 0, painted[st], adj);
    cout << ans << '\n';

    return 0;
}