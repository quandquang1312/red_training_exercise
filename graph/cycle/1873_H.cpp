// https://codeforces.com/problemset/problem/1873/H

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

vector<int> dijkstra(int st, vector<vector<int>>& graph) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, st});

    int n = graph.size();

    vector<int> dist(n + 1, INF);
    dist[st] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &v : graph[u]) {
            if (d + 1 < dist[v]) {
                dist[v] = d + 1;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

bool solve(int st, int en, vector<vector<int>>& graph, vector<int>& indegree, set<int>& circle) {
    int n = graph.size() - 1;
    vector<int> d1 = dijkstra(en, graph);
    vector<int> d2 = dijkstra(st, graph);

    // shortest d1 to cicle
    int p = -1, shortest = INF;
    for (auto &u : circle) {
        if (d1[u] < shortest) {
            shortest = min(shortest, d1[u]);
            p = u;
        }
    }

    if (d1[p] < d2[p]) return true;
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, st, en; cin >> n >> st >> en;
        
        vector<vector<int>> adj(n + 1);
        vector<int> indegree(n + 1, 0);
        for (int i=1; i<=n; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            indegree[u]++;
            indegree[v]++;
        }

        if (st == en) {
            cout << "No\n";
            continue;
        }

        queue<int> q;
        for (int i=1; i<=n; i++) {
            if (indegree[i] == 1) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 1) {
                    q.push(v);
                }
            }
        }

        // Marked circle
        set<int> circle;
        for (int i=1; i<=n; i++) {
            if (indegree[i] > 1) circle.insert(i);
        }

        if (circle.find(en) != circle.end()) {
            cout << "Yes\n";
        } else {
            bool ans = solve(st, en, adj, indegree, circle);
            cout << (ans ? "Yes" : "No") << "\n";
        }
    }

    return 0;
}