// https://usaco.org/index.php?page=viewproblem2&cpid=861

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX

vector<int> dijkstra(int n, vector<vector<pair<int, int>>>& graph) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, n});

    vector<int> dist(n + 1, INF);
    dist[n] = 0;

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

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("dining.in", "r", stdin);
        freopen("dining.out", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> initial_graph(n + 1), second_graph(n + 1);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        initial_graph[u].push_back({v, w});
        initial_graph[v].push_back({u, w});

        if (u != n && v != n) {
            second_graph[u].push_back({v, w});
            second_graph[v].push_back({u, w});
        }
    }
    vector<int> optimal = dijkstra(n, initial_graph);

    for (int i=0, u, y; i<k; i++) {
        cin >> u >> y;
        second_graph[n].push_back({u, optimal[u] - y});
        second_graph[u].push_back({n, optimal[u] - y});
    }

    vector<int> sec     = dijkstra(n, second_graph);

    for (int i=1; i<n; i++) {
        cout << i << ": " << optimal[i] << "-" << sec[i] << '\n';
        if (sec[i] <= optimal[i]) cout << "1\n";
        else cout << "0\n";
    }

    return 0;
}