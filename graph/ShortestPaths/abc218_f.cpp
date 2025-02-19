// https://atcoder.jp/contests/abc218/tasks/abc218_f

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back({v, i});
    }

    vector<int> dist(n + 1, INF);

    auto dijkstra = [&] (int i) -> vector<pair<int, int>> {
        dist.assign(n + 1, INF);
        dist[1] = 0;

        queue<int> q;
        q.push(1);

        vector<pair<int, int>> trace(n + 1, {-1, -1});

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (auto &[v, idx] : adj[u]) {
                if (idx == i) continue;
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    trace[v] = {u, idx};
                }
            }
        }

        return trace;
    };

    vector<pair<int, int>> trace = dijkstra(-1);
    vector<int> original_dist = dist;

    if (original_dist[n] != INF) {
        set<int> idx;
        for (int u=n; u!=1; u=trace[u].first) {
            int i = trace[u].second;
            idx.insert(i);
        }

        for (int i=0; i<m; i++) {
            if (idx.find(i) == idx.end()) {
                cout << original_dist[n] << "\n";
            } else {
                dijkstra(i);
                cout << (dist[n] == INF ? -1 : dist[n]) << "\n";
            }
        }
    } else {
        for (int i=0; i<m; i++) {
            cout << -1 << "\n";
        }
    }

    return 0;
}