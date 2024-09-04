// https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/description/

#include <bits/stdc++.h>
using namespace std;

#define int long long
int ans = -1;
const int MOD = 1e9 + 7;
/*
6
1 2
1 3
2 4
2 5
3 6
*/

/*
6
1 2
2 3
2 4
4 5
4 6
*/

/*
11
1 2
1 3
2 9
2 10
3 7
3 8
9 5
9 4
*/

vector<vector<int>> adj;
vector<int> dp;

int dfs(int u, int par) {
    if (dp[u] != -1) return dp[u];

    int ans = u;
    for (auto &v : adj[u]) {
        if (v == par) continue;

        ans = (ans + dfs(v, u)) % MOD;
    }

    return dp[u] = ans % MOD;
}

void rerooting(int u, int par) {
    for (auto &v : adj[u]) {
        if (v == par) continue;
        int original_u = dp[u], original_v = dp[v];

        // detach v from u
        dp[u] -= dp[v];

        ans = max(ans, ((dp[u] % MOD) * (dp[v] % MOD)) % MOD);

        // attach u to v
        dp[v] += dp[u];

        // cout << u << "-" << v << ": " << dp[u] << "*" << dp[v] << '\n';

        rerooting(v, u);

        // backtrack
        dp[u] = original_u;
        dp[v] = original_v;
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
    dp.resize(n + 1, -1);

    for (int i=0, u, v; i<(n - 1); i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);
    rerooting(0, 0);

    // for (int i=1; i<=n; i++) {
    //     cout << i << ": " << dp[i] << '\n';
    // }

    cout << ans << endl;

    return 0;
}