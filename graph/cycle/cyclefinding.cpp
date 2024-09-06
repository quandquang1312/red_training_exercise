// https://cses.fi/problemset/task/1197

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX
struct Edge {
    int u, v, w;
};

// find cycle bellman_ford
pair<bool, vector<int>> bellman_ford_findingcycle(int n, vector<Edge>& adj) {
    vector<int> dist(n + 1), trace(n + 1, -1);
    int x;

    for (int i=0; i<n; i++) {
        x = -1;
        for (Edge &e : adj) {
            int u = e.u, v = e.v, w = e.w;
            if (dist[u] + w < dist[v]) {
                dist[v] = max((int) -INF, dist[u] + w);
                trace[v] = u;
                x = v;
            }
        }
    }

    if (x == -1) return {false, {}};
    vector<int> ans;
    for (int i=0; i<n; i++) x = trace[x];
    for (int v=x ;; v=trace[v]) {
        ans.push_back(v);
        if (v == x && ans.size() > 1) break;
    }

    reverse(ans.begin(), ans.end());

    return {true, ans};
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
    vector<Edge> adj;
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj.push_back({u, v, w});
    }

    auto [rs, ans] = bellman_ford_findingcycle(n, adj);
    if (rs == false) cout << "NO\n";
    else {
        cout << "YES\n";
        for (auto &e : ans)
            cout << e << " ";
        
        cout << endl;
    }

    return 0;
}