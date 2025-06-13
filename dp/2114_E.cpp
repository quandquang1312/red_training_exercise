#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n + 1), parent(n + 1, -1);
        vector<vector<int>> dp(n + 1, vector<int>(2, -INF)), adj(n + 1);

        for (int i=1; i<=n; i++) cin >> arr[i];
        for (int i=1, u, v; i<n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        function<void(int, int)> getParent = [&] (int u, int p) {
            for (auto &v : adj[u]) {
                if (v == p) continue;
                parent[v] = u;
                getParent(v, u);
            }
        };

        getParent(1, 0);

        dp[1][0] = arr[1];
        dp[1][1] = 0;

        function<int(int, int)> dfs = [&] (int u, int sign) {
            if (dp[u][sign] != -INF) return dp[u][sign];

            int nxt = max(0LL, dfs(parent[u], 1 - sign));
            int current = (sign == 0 ? arr[u] : -arr[u]);
            return dp[u][sign] = max(0LL, current + nxt);
        };

        for (int i=1; i<=n; i++) {
            dfs(i, 0);
            dfs(i, 1);
        }

        for (int i=1; i<=n; i++) {
            cout << dp[i][0] << " ";
        }
        cout << "\n";
    }

    return 0;
}