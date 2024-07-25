// https://atcoder.jp/contests/abc333/tasks/abc333_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<bool> visited;

int dfs(int u) {
    if (visited[u]) return 0;
    visited[u] = true;

    int ans = 1;
    for (auto &v : adj[u]) {
        ans += dfs(v);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    adj.resize(n+1);
    visited.resize(n+1, false);

    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxnode = -1, ans = 0;
    visited[1] = true;
    for (int v=0; v<adj[1].size(); v++) {
        int tmp = dfs(adj[1][v]);
        maxnode = max(maxnode, tmp);
        ans += tmp;
    }

    cout << ans + 1 - maxnode << endl;

    return 0;
}