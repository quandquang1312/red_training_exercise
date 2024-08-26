// https://cses.fi/problemset/task/1672

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, INF));
    for (int i=1; i<=n; i++) adj[i][i] = 0;

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        if (w < adj[u][v]) adj[u][v] = adj[v][u] = w;
    }

    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            if (adj[i][k] == INF) continue;
            for (int j=1; j<=n; j++) {
                if (adj[k][j] == INF) continue;
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << (adj[u][v] == INF ? -1 : adj[u][v]) << '\n';
    }

    return 0;
}