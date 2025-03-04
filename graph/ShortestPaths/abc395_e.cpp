// https://atcoder.jp/contests/abc395/tasks/abc395_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, x;
    cin >> n >> m >> x;

    vector<vector<int>> adj[2];
    adj[0].assign(n + 1, vector<int>());
    adj[1].assign(n + 1, vector<int>());

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }

    vector<vector<int>> dist(2, vector<int>(n + 1, INF));
    dist[0][1] = 0;

    priority_queue<tuple<int, int, int>> pq;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [cost, u, p] = pq.top(); pq.pop();
        cost = -cost;

        if (cost > dist[p][u]) continue;

        for (auto &v : adj[p][u]) {
            if (dist[p][v] > dist[p][u] + 1) {
                dist[p][v] = dist[p][u] + 1;
                pq.push({-dist[p][v], v, p});
            }
        }

        int np = 1 - p;
        if (dist[np][u] > cost + x) {
            dist[np][u] = cost + x;
            pq.push({-dist[np][u], u, np});
        }
    }

    int ans = min(dist[0][n], dist[1][n]);
    cout << ans << "\n";

    return 0;
}