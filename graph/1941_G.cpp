// https://codeforces.com/problemset/problem/1941/G

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

vector<int> dijkstra(int st, vector<vector<pair<int, int>>>& graph) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, st});

    int n = graph.size();

    vector<int> dist(n + 1, INF);
    dist[st] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;

    while (tc--) {
        int n, w; cin >> n >> w;

        vector<tuple<int, int, int>> data(w);
        unordered_map<int, int> idx_c;

        int cnt = n + 1;
        for (int i=0, u, v, c; i<w; i++) {
            cin >> u >> v >> c;
            data[i] = {u, v, c};
            if (idx_c.find(c) == idx_c.end()) {
                idx_c[c] = cnt;
                cnt += 1;
            }
        }

        vector<vector<pair<int, int>>> adj(n + 1 + cnt);
        for (auto &[u, v, c] : data) {
            c = idx_c[c];
            adj[u].push_back({c, 1});
            adj[c].push_back({u, 1});

            adj[v].push_back({c, 1});
            adj[c].push_back({v, 1});
        }

        int e, b; cin >> e >> b;
        vector<int> dist = dijkstra(e, adj);

        int ans = dist[b] / 2;
        cout << ans << "\n";
    }

    return 0;
}