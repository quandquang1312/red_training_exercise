// https://www.acmicpc.net/problem/14875

#include <bits/stdc++.h>
using namespace std;

#define int long long

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
    vector<vector<int>> par(n + 1, vector<int>(2, 0));

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

        // attach u to v for every v
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

    for (int i=1; i<=n; i++) {
        dp[i] = max(dp[i], dp2[i]);
        par[i][0] = -dp[i].second;
    }

    int cur = (k & 1 ? par[1][0] : 1);
    for (int j=1; j<63; j++)
    {
        for (int i=1; i<=n; i++)
        par[i][j & 1] = par[par[i][j - 1 & 1]][j - 1 & 1];
        if ((k >> j) & 1LL)
        cur = par[cur][j & 1];
    }

    cout << cur;

    return 0;
}