// https://codeforces.com/contest/1144/problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> color;
bool bipartite = true;

// Bipartite using dfs
void dfs(int u, int c) {
    color[u] = c;
    for (auto v : adj[u]) {
        if (color[v] == -1)
            dfs(v, c ^ 1);
        else if (color[v] == color[u])
            bipartite = false;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    adj.resize(n + 1);
    color.assign(n + 1, -1);

    vector<pair<int, int>> edges;
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }

    dfs(1, 0);

    if (!bipartite) {
        cout << "NO\n";
    } else {
        // will direct from color -1 to color 2
        cout << "YES\n";
        for (int i=0; i<m; i++) {
            auto [u, v] = edges[i];
            if (color[u] == 0) cout << '0';
            else cout << '1';
        }
        cout << "\n";
    }

    return 0;
}