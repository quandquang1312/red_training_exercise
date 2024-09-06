// https://open.kattis.com/problems/shortestpath3?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void bellman_ford(int s, int n, vector<vector<pair<int, int>>>& adj, int nq) {
    int x;
    vector<int> dist(n, INF), trace(n, -1);
    dist[s] = 0;

    for (int j=0; j<n-1; j++) {
        for (int u=0; u<n; u++) {
            if (dist[u] == INF) continue;
            for (auto &[v, w] : adj[u]) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }

    queue<int> q;

    for (int u=0; u<n; u++) {
        if (dist[u] == INF) continue;
        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) q.push(v);
        }
    }

    vector<bool> neg(n, false);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        neg[u] = true;
        for (auto &[v, w] : adj[u]) {
            if (neg[v]) continue;
            q.push(v);
        }
    }

    while (nq--) {
        int x; cin >> x;
        if (neg[x]) cout << "-Infinity\n";
        else if (dist[x] == INF) cout << "Impossible\n";
        else cout << dist[x] << '\n';
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, q, s, tc = 0;
    while (cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) break;
        if (tc++) cout << '\n';

        vector<vector<pair<int, int>>> adj(n);
        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
        }

        bellman_ford(s,n,adj,q);
    }

    return 0;
}