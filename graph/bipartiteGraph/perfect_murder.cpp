// https://vjudge.net/contest/174055#problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

int maximum_matching(int n, int m, const vector<vector<int>>& adj) {
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

    return hopcroftKarp();
}


const int INF = 1e9;

int maximum_matching(int n, const vector<vector<int>>& adj) {
    vector<int> matchL(n + 1, 0);
    vector<int> matchR(n + 1, 0);
    vector<int> dist(n + 1, INF);
    
    vector<int> side(n + 1, -1);
    
    function<void(int)> dfs_color = [&](int u) {
        queue<int> q;
        q.push(u);
        side[u] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int nei : adj[v]) {
                if (side[nei] == -1) {
                    side[nei] = 1 - side[v];
                    q.push(nei);
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (side[i] == -1) {
            dfs_color(i);
        }
    }

    auto bfs = [&]() -> bool {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (side[u] == 0 && matchL[u] == 0) {
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

    function<int()> hopcroftKarp = [&]() -> int {
        int matching = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++) {
                if (side[i] == 0 && matchL[i] == 0 && dfs(i)) {
                    matching++;
                }
            }
        }
        return matching;
    };

    return hopcroftKarp();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int n, m; cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        vector<bool> visited(n + 1, false);

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int ans = n - maximum_matching(n, adj);

        cout << "Case " << t << ": " << ans << "\n";
    } 

    return 0;
}