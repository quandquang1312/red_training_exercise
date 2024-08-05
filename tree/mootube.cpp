// https://usaco.org/index.php?page=viewproblem2&cpid=788

#include <bits/stdc++.h>
using namespace std;

int dfs(int node, int par, vector<vector<pair<int, int>>>& adj, int k) {
    int ans = 1;

    for (auto &[v, c] : adj[node]) {
        if (c >= k && v != par) {
            ans += dfs(v, node, adj, k);
        }
    }

    return ans;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #if 1
        freopen("mootube.in", "r", stdin);
        freopen("mootube.out", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    vector<vector<pair<int, int>>> adj(n+1);
    for (int i=0; i<n-1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    while (q--) {
        int u, k;
        cin >> k >> u;
        cout << dfs(u, 0, adj, k) - 1 << '\n';
    }

    return 0;
}