// https://usaco.org/index.php?page=viewproblem2&cpid=969

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX

int dijkstra(int minf, int n, vector<vector<tuple<int, int, int>>>& adj) {
    priority_queue<pair<int, int>> pq;
    pq.push({0, 1});
    vector<int> dist(n + 1, INF);
    dist[1] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        d = -d;

        if (d > dist[u]) continue;

        for (auto &[v, w, f] : adj[u]) {
            if (f < minf) continue;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({-dist[v], v});
            }
        }
    }

    return dist[n];
}

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

    vector<int> flist;
    for (int i=0, u, v, w, f; i<m; i++) {
        cin >> u >> v >> w >> f;
        adj[u].push_back({v, w, f});
        adj[v].push_back({u, w, f});
        flist.push_back(f);
    }

    int ans = -1;
    for (int i=0; i<flist.size(); i++) {
        int tmp_dst = dijkstra(flist[i], n, adj);
        if (tmp_dst == INF) continue;
        double ratio = (double) flist[i] / (double) tmp_dst;
        ans = max(ans, (int)(ratio * 1e6));
    }

    cout << ans << endl;

    return 0;
}