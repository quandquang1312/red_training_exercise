// https://cses.fi/problemset/task/1696

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n + m + 1);
    for (int i=0, u, v; i<k; i++) {
        cin >> u >> v;
        adj[u].push_back(v + n);
        adj[v + n].push_back(u);
    }
    
    vector<int> matchL(n + 1, 0);
    vector<int> matchR(n + m + 1, 0);
    vector<int> dist(n + 1, INF);
    
    auto bfs = [&]() -> bool {
        queue<int> q;
        for (int u=1; u<=n; u++) {
            if (matchL[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == 0) continue;
            for (int v : adj[u]) {
                if (matchR[v] == 0) {
                    dist[0] = dist[u] + 1;
                } else if (dist[matchR[v]] == INF) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return dist[0] != INF;
    };
    
    function<bool(int)> dfs = [&](int u) -> bool {
        if (u != 0) {
            for (int v : adj[u]) {
                if (matchR[v] == 0 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                    matchL[u] = v;
                    matchR[v] = u;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    };

    function<int()> hopcroftKarp = [&] () -> int {
        int matching = 0;
        while (bfs()) {
            for (int i=1; i<=n; i++) {
                if (matchL[i] == 0 && dfs(i)) {
                    matching++;
                }
            }
        }
        return matching;
    };

    int ans = hopcroftKarp();
    
    cout << ans << "\n";
    for (int i=1; i<=n; i++) {
        if (matchL[i] != 0) {
            cout << i << " " << matchL[i] - n << "\n";
        }
    }
    
    return 0;
}
