// https://codeforces.com/contest/1144/problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> color;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    adj.resize(n + 1);
    color.assign(n + 1, 2);

    vector<pair<int, int>> edges;
    for (int i=0, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }

    queue<int> q;
    q.push(1);

    bool isBipartite = true;
    // color will be -1 and 2
    while (!q.empty() && isBipartite)
    {
        int u = q.front(); q.pop();
        for (auto &v : adj[u]) {
            if (color[v] == 2) {
                color[v] = 1 - color[u];
                q.push(v);
            } else if (color[v] == color[u]) {
                isBipartite = false;
                break;
            }
        }
    }

    if (!isBipartite) {
        cout << "NO\n";
    } else {
        // will direct from color 1 to color 2
        cout << "YES\n";
        for (int i=0; i<m; i++) {
            auto [u, v] = edges[i];
            if (color[u] == -1) cout << '0';
            else cout << '1';
        }
    }

    return 0;
}