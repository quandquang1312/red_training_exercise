// https://cses.fi/problemset/task/1707

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    vector<vector<int>> dist(n+1, vector<int>(n+1, 1e9));

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 1e9;
    for (int i=1; i<=n; i++) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[i][i] = 0;
        pq.push({0,i});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[i][u]) continue;

            for (auto &v : adj[u]) {
                if (dist[i][v] == 1e9) {
                    dist[i][v] = dist[i][u] + 1;
                    pq.push({dist[i][v], v});
                } else if (dist[i][v] >= dist[i][u]) {
                    ans = min(ans, dist[i][v] + dist[i][u] + 1);
                }
            }
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << '\n';

    return 0;
}