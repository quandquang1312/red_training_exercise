// https://open.kattis.com/problems/intercept

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX

vector<vector<pair<int, int>>> adj, adj_trans;
vector<vector<int>> adj_both;
int s, t;

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

void proprocess(int n) {
    adj.resize(n + 1);
    adj_both.resize(n + 1);
    adj_trans.resize(n + 1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    proprocess(n);

    for (int i=0, u, v; i<m; i++) {
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj_trans[v].push_back({u, w});
        adj_both[u].push_back(v);
        adj_both[v].push_back(u);
    }

    cin >> s >> t;

    vector<int> d1 = dijkstra(s, adj);
    vector<int> d2 = dijkstra(t, adj_trans);

    int shortestPath = d1[t];

    set<int> ans;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    vector<bool> pushed(n + 1, false);
    pushed[s] = true;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (pq.empty()) ans.insert(u);
        for (auto &[v, w] : adj[u]) {
            if (pushed[v]) continue;
            if (d1[u] + w + d2[v] == shortestPath) {
                pq.push({d1[v], v});
                pushed[v] = true;
            }
        }
    }

    for (auto &e : ans) cout << e << " ";
    cout << '\n';

    return 0;
}