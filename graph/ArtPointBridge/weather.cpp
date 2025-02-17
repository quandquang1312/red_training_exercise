// https://oj.vnoi.info/problem/weather

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> dfs_num, dfs_low, articulation, parent;
vector<pair<int, int>> bridges;
int timer, n, m, rootChildren, root;

void dfs(int u)
{
    dfs_num[u] = dfs_low[u] = timer++;

    for (auto v : adj[u])
    {
        if (dfs_num[v] == -1) {
            parent[v] = u;

            if (u == root) ++rootChildren;

            dfs(v);

            if (dfs_low[v] >= dfs_num[u])
                articulation[u] = 1;
            if (dfs_low[v] > dfs_num[u]) {
                bridges.push_back({u, v});
            }

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void find_bridges()
{
    timer = 0;
    parent.resize(n + 1, -1);
    dfs_low.resize(n + 1, 0);
    dfs_num.resize(n + 1, -1);
    articulation.resize(n + 1, 0);

    for (int i=1; i<=n; i++) {
        if (dfs_num[i] == -1) {
            root = i, rootChildren = 0;
            dfs(i);
            articulation[root] = (rootChildren > 1);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;

    adj.assign(n + 1, vector<int>());

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_bridges();

    vector<bool> visited(n + 1, false);

    function<int(int)> dfs = [&] (int u) -> int {
        int ans = 1;
        visited[u] = true;

        for (auto &v : adj[u]) {
            if (!visited[v]) ans += dfs(v);
        }

        return ans;
    };

    int ans = 0;
    for (auto &[u, v] : bridges) {
        visited.assign(n + 1, false);
        visited[v] = true;

        int c = dfs(u);
        ans += (c * (n - c));
    }

    cout << ans << "\n";

    return 0;
}