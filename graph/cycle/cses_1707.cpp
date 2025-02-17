// https://cses.fi/problemset/task/1707

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);

    auto bfs = [&] (int st) -> int {
        queue<int> q;
        q.push(st);

        dist.assign(n + 1, -1);
        dist[st] = 0;

        int ans = INF;
        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (auto &v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                } else if (dist[v] >= dist[u]) {
                    ans = min(ans, 1 + dist[u] + dist[v]);
                }
            }
        }

        return ans;
    };

    int ans = INF;
    for (int i=1; i<=n; i++) {
        ans = min(ans, bfs(i));
    }

    cout << (ans == INF ? -1 : ans) << "\n";

    return 0;
}