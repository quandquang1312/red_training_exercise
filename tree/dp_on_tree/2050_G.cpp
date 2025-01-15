// https://codeforces.com/problemset/problem/2050/G

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dp;

pair<int, int> dfs(int u, int p, const vector<vector<int>>& adj) {
    int max_child_1 = 0;
    int max_child_2 = 0;
    int num_child = 0;

    for (auto &v : adj[u]) {
        if (v == p) continue;
        num_child++;
        auto [dfs_v, _] = dfs(v, u, adj);
        if (dfs_v >= max_child_1) {
            max_child_2 = max_child_1;
            max_child_1 = dfs_v;
        } else if (dfs_v > max_child_2) max_child_2 = dfs_v;
    }

    if (num_child >= 2) return dp[u] = {max(num_child, num_child - 1 + max_child_1), max(0, num_child - 2 + max_child_1 + max_child_2) + (u != 1)};
    if (num_child == 1) return dp[u] = {max(num_child, max_child_1), 0};
    if (num_child == 0) return dp[u] = {0, 0};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vector<int>> adj(n + 1);
        dp.assign(n + 1, {0, 0});

        for (int i=1, u, v; i<n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0, adj);
        int ans = 0;
        for (int i=1; i<=n; i++) {
            ans = max(ans, max(dp[i].first + (i != 1), dp[i].second));
        }

        cout << ans << "\n";
    }

    return 0;
}