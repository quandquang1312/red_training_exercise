// https://open.kattis.com/problems/shortestpath1?tab=metadata

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m, queries, s;
    while (cin >> n >> m >> queries >> s) {
        if (n + m + queries + s == 0) break;

        vector<vector<pair<int, int>>> adj(n);
        vector<int> dist(n, 1e9);
        dist[s] = 0;

        
        for (int i=0; i<m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
        }

        set<pair<int, int>> pq;
        for (int i=0; i<n; i++)
            pq.insert({dist[i], i});

        while (!pq.empty())
        {
            auto [d, u] = *pq.begin();
            pq.erase(pq.begin());
            vector<pair<int, int>>& neighbors = adj[u];

            for (const auto &[v, w] : neighbors)
            {
                if (dist[u] + w < dist[v]) {
                    pq.erase(pq.find({dist[v], v}));
                    dist[v] = dist[u] + w;
                    pq.insert({dist[v], v});
                }
            }
        }

        while (queries--) {
            int dest; cin >> dest;
            cout << (dist[dest] == 1e9 ? "Impossible" : to_string(dist[dest])) << endl;
        }
        cout << endl;
    }

    return 0;
}