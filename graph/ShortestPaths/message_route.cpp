// https://cses.fi/problemset/task/1667

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
    vector<vector<pair<int, int>>> adj(n+1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back({1, v});
        adj[v].push_back({1, u});
    }

    vector<int> dist(n+1, 1e9), trace(n+1, -1);
    dist[1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[1], 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;
        
        for (auto &[w, v] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                trace[v] = u;
            }
        }
    }

    if (dist[n] == 1e9) printf("IMPOSSIBLE\n");
    else {
        printf("%d\n", dist[n] + 1);
        int node = n;
        vector<int> ans;
        while (trace[node] != -1) {
            ans.push_back(node);
            node = trace[node];
        }
        ans.push_back(1);
        reverse(ans.begin(), ans.end());

        for (auto &e : ans) {
            printf("%d ", e);
        }
    }

    return 0;
}