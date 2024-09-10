// https://open.kattis.com/problems/caveexploration

#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> dfs_num, dfs_low, parent;
vector<bool> visited;
int timer;

void find_bridge(int u)
{
    dfs_num[u] = dfs_low[u] = timer++;

    for (auto &[status, v] : adj[u])
    {
        if (dfs_num[v] == -1) {
            parent[v] = u;

            find_bridge(v);

            if (dfs_low[v] > dfs_num[u]) status = 0;

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int dfs(int u) {
    if (visited[u]) return 0;
    visited[u] = true;

    int ans = 1;
    for (auto &[status, v] : adj[u]) {
        if (status == 0 || visited[v]) continue;

        ans += dfs(v);
    }

    return ans;
}

void preprocess(int n) {
    timer = 0;
    adj.resize(n + 1);
    parent.assign(n + 1, -1);
    dfs_low.assign(n + 1, 0);
    dfs_num.assign(n + 1, -1);
    visited.assign(n + 1, false);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    preprocess(n);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back({1, v});
        adj[v].push_back({1, u});
    }

    find_bridge(0);
    int ans = dfs(0);

    cout << ans << '\n';

    return 0;
}