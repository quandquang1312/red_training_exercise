// https://cses.fi/problemset/task/1202

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("tests/1.in", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> cnt(n + 1, 0), dist(n + 1, INF);
    vector<bool> visited(n + 1, false);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<pair<int, int>> flights(n + 1, {INF, 0});
    
    dist[1] = 0, cnt[1] = 1;
    flights[1] = {0, 0};

    // dist, u
    priority_queue<tuple<int, int>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        d = -d;

        if (visited[u]) continue;
        visited[u] = true;

        for (auto &[v, w] : adj[u]) {
            if (d + w > dist[v]) continue;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u];
                // cout << u << "=>" << v << ": " << dist[v] << " | " << cnt[u] << "-" << cnt[v] << '\n';
                flights[v].first  = flights[u].first + 1;
                flights[v].second = flights[u].second + 1;
                pq.push({-dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
                // cout << u << "->" << v << ": " << dist[v] << " | " << cnt[u] << "-" << cnt[v] << '\n';
                flights[v].first  = min(flights[v].first, flights[u].first + 1);
                flights[v].second = max(flights[v].second, flights[u].second + 1);
            }
        }
    }

    cout << dist[n] << " " << cnt[n] << " " << flights[n].first << " " << flights[n].second << '\n';

    return 0;
}