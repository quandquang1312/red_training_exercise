// https://cses.fi/problemset/task/1671

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
    vector<int> dist(n + 1, INF);
    dist[1] = 0;

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    priority_queue<pair<int, int>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        d = -d;

        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({-dist[v], v});
            }
        }
    }

    for (int i=1; i<=n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}