// https://codeforces.com/contest/1324/problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<int> arr(n + 1);
    for (int i=1; i<=n; i++) cin >> arr[i];

    vector<vector<int>> adj(n + 1);
    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> dp(n + 1, {-1, -1});

    function<pair<int, int>(int, int)> dfs = [&] (int u, int p) -> pair<int, int> {
        pair<int, int> cur = {0, 0};

        if (arr[u] == 1) cur.first++;
        else cur.second++;

        for (auto &v : adj[u]) {
            if (v == p) continue;

            dfs(v, u);
            auto dv = dp[v];

            if (dv.first > dv.second) {
                cur.first += dv.first;
                cur.second += dv.second;
            }
        }

        return dp[u] = cur;
    };

    vector<pair<int, int>> ans(n + 1);

    function<void(int, int)> reroot = [&] (int u, int p) -> void {
        ans[u] = dp[u];

        for (auto &v : adj[u]) {
            if (v == p) continue;

            // save original
            auto dv = dp[v], du = dp[u];

            // detach v from u
            if (dp[v].first > dp[v].second) {
                dp[u].first -= dp[v].first;
                dp[u].second -= dp[v].second;
            }

            // attach u to v
            if (dp[u].first > dp[u].second) {
                dp[v].first += dp[u].first;
                dp[v].second += dp[u].second;
            }

            // reroot
            reroot(v, u);

            // backtrack
            dp[v] = dv;
            dp[u] = du;
        }
    };

    dfs(1, 0);
    reroot(1, 0);

    for (int i=1; i<=n; i++) {
        cout << ans[i].first - ans[i].second << " ";
    }

    return 0;
}