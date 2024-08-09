// https://codejam.lge.com/problem/25685

#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[100010][2];
vector<vector<bool>> visited;

int dfs(int u, int choose, vector<vector<int>>& adj, vector<int>& arr) {
    int ans = (choose == 1 ? arr[u] : 0), sm = 0;

    if (adj[u].size() == 0) return dp[u][choose] = ans;
    if (visited[u][choose]) return dp[u][choose];

    visited[u][choose] = true;
    if (choose == 0) {
        int min_diff = LLONG_MAX;
        bool added = false; 

        if (adj[u].size() == 1)
            return dp[u][choose] = ans + dfs(adj[u][0], 1, adj, arr);

        for (auto &v : adj[u]) {
            int dfsv_1 = dfs(v, 0, adj, arr);
            int dfsv_2 = dfs(v, 1, adj, arr);
            min_diff = min(min_diff, dfsv_1 - dfsv_2);

            if (dfsv_2 >= dfsv_1) added = true;
            sm += max(dfsv_1, dfsv_2);
        }

        if (!added) sm -= min_diff;
        return dp[u][choose] = ans + sm;
    } else {
        for (auto &v : adj[u]) {
            int dfsv = dfs(v, 0, adj, arr);
            sm += dfsv;
        }

        return dp[u][choose] = ans + sm;
    }
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
        vector<int> arr(n+1);
        vector<vector<int>> adj(n+1);
        visited.assign(n+1, vector<bool>(2, false));
        for (int i=1; i<=n; i++) cin >> arr[i];

        int r;
        for (int u=1, v; u<=n; u++) {
            cin >> v;
            if (v == 0) r = u;
            else adj[v].push_back(u); 
        }

        dfs(r, 1, adj, arr);
        dfs(r, 0, adj, arr);

        int ans = max(dp[r][0], dp[r][1]);
        cout << ans << '\n';
    }

    return 0;
}