// https://cses.fi/problemset/task/1691

#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> path;
vector<bool> visited;

// eulerian cycle undirected graph
void dfs(int u) {
    while (!adj[u].empty()) {
        auto [street_idx, v] = adj[u].back();
        adj[u].pop_back();

        if (visited[street_idx]) continue;
        visited[street_idx] = true;

        dfs(v);
    }

    path.push_back(u);
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

    adj.resize(n + 1);
    visited.resize(m, false);
    vector<int> indegree(n + 1, 0);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back({i, v});
        adj[v].push_back({i, u});
        indegree[u]++, indegree[v]++;
    }

    for (int i=1; i<=n; i++) {
        if (indegree[i] % 2) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(1);

    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto &e : path) {
        cout << e << " ";
    }

    return 0;
}