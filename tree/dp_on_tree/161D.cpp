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

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    int ans = 0;

    function<void(int, int)> dfs = [&] (int u, int p) -> void {
        dp[u][0] = 1;
        for (auto &v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);

            // all the previous child node copare to v
            for (int i=1; i<=k; i++) {
                ans += dp[u][i-1] * dp[v][k-i];
            }

            // update result of v to u
            for (int i=1; i<=k; i++) {
                dp[u][i] += dp[v][i-1];
            }
        }
    };

    dfs(1, 0);

    cout << ans << "\n";

    return 0;
}