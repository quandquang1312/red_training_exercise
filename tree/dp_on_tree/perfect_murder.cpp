// https://vjudge.net/contest/174055#problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int n, m; cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        vector<bool> visited(n + 1, false);

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        function<int(int, int, int)> dfs = [&] (int u, int status, int p) -> int {
            visited[u] = true;
            if (dp[u][status] != -1) return dp[u][status];

            int ans = status;

            for (auto &v : adj[u]) {
                if (v == p) continue;

                if (status == 0) ans += max(dfs(v, 1, u), dfs(v, 0, u));
                else ans += dfs(v, 0, u);
            }

            return dp[u][status] = ans;
        };

        int ans = 0;
        for (int i=1; i<=n; i++) {
            if (!visited[i])
                ans += max(dfs(i, 0, 0), dfs(i, 1, 0));
        }

        cout << "Case " << t << ": " << ans << "\n";
    } 

    return 0;
}