// https://cses.fi/problemset/task/1130

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200100

int dp[MAXN][2];

int dfs(int u, int par, int match, vector<vector<int>>& adj) {
    if (dp[u][match] != -1) return dp[u][match];
    if (match == 0) {
        int ans = 0;
        vector<pair<int, int>> diff(adj[u].size());

        int max_diff = 0;
        for (int i=0; i<adj[u].size(); i++) {
            int v = adj[u][i];
            if (par == v) continue;
            diff[i].first = 1 + dfs(v, u, 1, adj);
            diff[i].second = dfs(v, u, 0, adj);
            ans += diff[i].second;
            max_diff = max(max_diff, diff[i].first - diff[i].second);
        }

        return dp[u][match] = ans += max_diff;
    } else {
        int ans = 0;
        for (auto &v : adj[u]) {
            if (par == v) continue;
            int nmv = dfs(v, u, 0, adj);
            ans += nmv;
        }

        return dp[u][match] = ans;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    memset(dp, -1, sizeof dp);

    int r = -1;
    vector<vector<int>> adj(n+1);
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = dfs(1, 0, 0, adj);
    cout << ans << "\n";

    return 0;
}