// https://www.acmicpc.net/problem/14875

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    vector<int> arr(n + 1);

    for (int i=1; i<=n; i++) cin >> arr[i];
    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> dp(n + 1, {-INF, -1});
    vector<pair<int, int>> dp2(n + 1, {-INF, -1});

    function<void(int, int)> dfs = [&] (int u, int p) {
        for (auto &v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            dp[u] = max({dp[u], {dp[v].first - 1, dp[v].second}, {arr[v] - 1, -v}});
        }
    };

    function<void(int, int)> reroot = [&] (int u, int p) {
        pair<int, int> tmp = {dp2[u].first - 1, dp2[u].second};
        tmp = max(tmp, {arr[u] - 1, -u});
        for (int i=0; i<adj[u].size(); i++) {
            int v = adj[u][i];
            dp2[v] = max(dp2[v], tmp);
            tmp = max({dp2[v], {dp[v].first - 2, dp[v].second}, {arr[v] - 2, -v}});
        }

        tmp = {dp2[u].first - 1, dp2[u].second};
        tmp = max(tmp, {arr[u] - 1, -u});
        for (int i=adj[u].size() - 1; i>=0; i--) {
            int v = adj[u][i];
            dp2[v] = max(dp2[v], tmp);
            tmp = max({dp2[u], {dp[v].first - 2, dp[v].second}, {arr[v] - 2, -v}});
        }

        for (auto &v : adj[u]) {
            if (v == p) continue;
            reroot(v, u);
        }
    };

    dfs(1, 0);
    reroot(1, 0);

    for (int i=1; i<=n; i++) dp[i] = max(dp[i], dp2[i]);

    int cur = 1;
    for (int i=1; i<=k; i++) {
        int next = -dp[cur].second;
        cur = next;
    }

    cout << cur << "\n";

    return 0;
}