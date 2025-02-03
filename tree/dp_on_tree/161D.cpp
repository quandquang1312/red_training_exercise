// https://codeforces.com/contest/161/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n + 1, 0);
    int ans = 0;
    function<int(int, int)> dfs = [&] (int u, int p) -> int {
        dp[u] = 0;

        set<int> nodes;
        for (auto &v : adj[u]) {
            if (v == p) continue;
            dp[u]++;
            int nodes_v = dfs(v, u);
            if (nodes_v >= k - 1) ans++;

            auto it = nodes.lower_bound(k - nodes_v);

            nodes.insert(nodes_v);
        }

        if (nodes.empty()) return dp[u];

        auto e = nodes.begin();
        while (e != nodes.end()) {
            int v = *e;
            if (v >= k) ans += v * std::distance(e, nodes.end());
            else {
                auto it = nodes.lower_bound(k - v);
                ans += std::distance(it, nodes.end());
            }
            e++;
        }

        return dp[u];
    };

    dfs(1, 0);

    cout << ans << "\n";


    return 0;
}