// https://codeforces.com/problemset/problem/1528/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<pair<int, int>> LR(n + 1);
        vector<vector<int>> adj(n + 1);

        for (int i=1; i<=n; i++) cin >> LR[i].first >> LR[i].second;

        for (int i=1, u, v; i<n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        // dp[i][l/r] : the maximum beauty of the subtree of i when choose l/r for node i

        function<int(int, int, int)> dfs = [&] (int u, int p, int lr) {
            if (dp[u][lr] != -1) return dp[u][lr];
            dp[u][lr] = 0;

            int ans = 0;
            int beauty = (lr == 0 ? LR[u].first : LR[u].second);

            for (auto &v : adj[u]) {
                if (v == p) continue;
                // choose l for node v
                int ans = abs(beauty - LR[v].first) + dfs(v, u, 0); 

                // choose r
                ans = max(ans, abs(beauty - LR[v].second) + dfs(v, u, 1));

                dp[u][lr] += ans;
            }

            return dp[u][lr];
        };

        int ans = max(dfs(1, 0, 0), dfs(1, 0, 1));
        cout << ans << "\n";
    }

    return 0;
}