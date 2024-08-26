// https://cses.fi/problemset/task/1195

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

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<int>> min_dist(n + 1, vector<int>(2, INF));
    min_dist[0][0] = min_dist[0][1] = 0;

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    priority_queue<tuple<int, int, int>> pq;
    pq.push({0, 0, 1});

    while (!pq.empty()) {
        auto [d, used, u] = pq.top();
        pq.pop();

        d = -d;

        if (d > min_dist[u][used]) continue;

        for (auto &[v, w] : adj[u]) {
            if (used == 0) { // now try to use the discount on this flight
                if (d + w/2 < min_dist[v][1]) {
                    min_dist[v][1] = d + w/2;
                    pq.push({-min_dist[v][1], 1, v});
                }
            }

            // ignore it, not use the discount
            if (d + w < min_dist[v][used]) {
                min_dist[v][used] = d + w;
                pq.push({-min_dist[v][used], used, v});
            }
        }
    }
    cout << min_dist[n][1] << '\n';

    return 0;
}