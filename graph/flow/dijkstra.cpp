// https://vjudge.net/problem/UVA-10806

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<vector<pair<int, int>>> graph;
vector<vector<bool>> used;
vector<int> trace;

int dijkstra(int st, int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, st});

    vector<int> dist(n + 1, INF);
    dist[st] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (used[u][v]) continue;
            if (d + w < dist[v]) {
                trace[v] = u;
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[n];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n == 0) break;

        graph.assign(n + 1, vector<pair<int, int>>());
        trace.assign(n + 1, -1);
        used.assign(n + 1, vector<bool>(n + 1, false));

        int m; cin >> m;
        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        int ans = dijkstra(1, n);
        if (ans == INF) {
            cout << "Back to jail\n";
            continue;
        }

        for (int u=n; trace[u] != -1; u = trace[u]) {
            used[trace[u]][u] = true;

            for (int i=0; i<graph[u].size(); i++) {
                if (graph[u][i].first == trace[u]) {
                    graph[u][i].second *= -1;
                    break;
                }
            }
        }

        ans += dijkstra(1, n);

        if (ans >= INF) cout << "Back to jail\n";
        else cout << ans << "\n";
    }

    return 0;
}