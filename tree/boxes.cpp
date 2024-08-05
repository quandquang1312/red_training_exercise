// https://open.kattis.com/problems/boxes?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 2 * 1e5 + 10;

int dp[MAXN];

int dfs(int u, vector<vector<int>>& adj) {
    if (dp[u] != 0) return dp[u];

    int ans = 1;
    for (auto &v : adj[u]) {
        if (dp[v] == 0) ans += dfs(v, adj);
    }

    return dp[u] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<vector<int>> adj(n+1);

    for (int i=1; i<=n; i++) {
        int pr; cin >> pr;
        if (pr) {
            adj[pr].push_back(i);
        }
    }

    int q; cin >> q;
    while (q--) {
        int m, x; cin >> m;
        memset(dp, 0, sizeof dp);

        int ans = 0;
        for (int i=0; i<m; i++) {
            cin >> x;
            if (dp[x] == 0) ans += dfs(x, adj); 
        }

        cout << ans << '\n';
    }

    return 0;
}