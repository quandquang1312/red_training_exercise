// https://usaco.org/index.php?page=viewproblem2&cpid=969

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
    #else
        freopen("pump.in", "r", stdin);
        freopen("pump.out", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<tuple<int, int, int>>> adj(n + 1);
    for (int i=0, u, v, w, f; i<m; i++) {
        cin >> u >> v >> w >> f;
        adj[u].push_back({v, w, f});
        adj[v].push_back({u, w, f});
    }

    priority_queue<tuple<int, int, int>> pq;
    pq.push({0, 1, INF});
    vector<pair<int, int>> dist(n + 1, {INF, INF});
    dist[1] = {0, INF};

    while (!pq.empty()) {
        auto [d, u, cf] = pq.top();
        pq.pop();

        d = -d;

        if (d > dist[u].first) continue;

        for (auto &[v, w, f] : adj[u]) {
            if (d + w < dist[v].first) {
                dist[v] = {d + w, min(cf, f)};
                pq.push({-dist[v].first, v, min(cf, f)});
            }
        }
    }

    int ans = ((1.0 * dist[n].second) / (1.0 * dist[n].first)) * 1e6;
    cout << ans << '\n';

    return 0;
}