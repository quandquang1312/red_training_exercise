// https://atcoder.jp/contests/abc368/tasks/abc368_d

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> val;

int dfs(int u, int par) {
    int ans = 0, add = 0;

    for (auto &v : adj[u]) {
        if (v == par) continue;
        int dfs_v = dfs(v, u);
        if (dfs_v > 0) add = 1;
        ans += dfs_v;
    }

    if (val[u] || add) ans++;
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, k;
    cin >> n >> k;

    adj.resize(n + 1);
    val.resize(n + 1, 0);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int rt = -1;
    for (int i=0, u; i<k; i++) {
        cin >> u;
        val[u] = 1;
        rt = u; 
    }

    int ans = dfs(rt, 0);
    cout << ans << '\n';

    return 0;
}