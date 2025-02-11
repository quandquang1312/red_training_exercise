// https://vjudge.net/contest/174055#problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e9;

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int n, m; cin >> n >> m;

        vector<vector<int>> adj(n + m + 1);
        vector<tuple<int, int, int>> men(n + 1);
        for (int i=1, height, age, status; i<=n; i++) {
            cin >> height >> age >> status;
            men[i] = {height, age, status};
        }

        for (int j=1, height, age, status; j<=m; j++) {
            cin >> height >> age >> status;

            for (int i=1; i<=n; i++) {
                auto [h, a, s] = men[i];
                if ((abs(height - h) <= 12) && (abs(age - a) <= 5) && ((s ^ status == 0))) {
                    adj[i].push_back(j + n);
                    adj[j + n].push_back(i);
                }
            }
        }

        int ans = maximum_matching(n, m, adj);
        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}