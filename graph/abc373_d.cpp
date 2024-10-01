// https://atcoder.jp/contests/abc373/tasks/abc373_d

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9 + 7;

vector<bool> visited;
vector<int> ans;

int dfs(int u, vector<vector<pair<int, int>>>& adj) {
    if (visited[u]) return -INF;
    visited[u] = true;

    int ans = -INF;
    for (auto &[v, w] : adj[u]) {
        ans = max(ans, INF);
        if (!visited[u]) dfs(v, adj);
    }

    return ans;
}

vector<int> getMaxnNodeCC(int n, vector<vector<pair<int, int>>>& adj) {
    vector<int> max_node;
    visited.assign(n + 1, false);
    for (int i=1; i<=n; i++) {
        if (!visited[i]) continue;
        int ans = dfs(i, adj);
        max_node.push_back(ans);
    }

    return max_node;
}

void assign_value(int u, vector<vector<pair<int, int>>>& adj) {
    if (visited[u]) return;
    visited[u] = true;

    for (auto &[v, w] : adj[u]) {
        ans[v] = ans[u] - w;
        if (!visited[v]) assign_value(v, adj); 
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<pair<int, int>>> mv(n + 1);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        mv[v].push_back({u, w});
    }

    vector<int> max_node = getMaxnNodeCC(n, adj);

    ans.assign(n + 1, 0);
    for (auto &e : max_node) {
        ans[e] = 1e9;
        assign_value(e, mv);
    }

    for (int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}