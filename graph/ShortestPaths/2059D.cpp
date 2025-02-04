// https://codeforces.com/contest/2059/problem/D

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n, s1, s2;
        cin >> n >> s1 >> s2;

        vector<vector<int>> adj1(n + 1), adj2(n + 1);

        int m1; cin >> m1;
        for (int i=0, u, v; i<m1; i++) {
            cin >> u >> v;
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }

        int m2; cin >> m2;
        for (int i=0, u, v; i<m2; i++) {
            cin >> u >> v;
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }

        vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
        dist[s1][s2] = 0;

        priority_queue<tuple<int, int, int>> pq;
        pq.push({0, s1, s2});

        while (!pq.empty()) {
            auto [cost, u, v] = pq.top();
            cost = -cost;
            pq.pop();

            if (cost > dist[u][v]) continue;

            for (auto &to1 : adj1[u]) {
                for (auto &to2 : adj2[v]) {
                    if (dist[to1][to2] > (cost + abs(to1 - to2))) {
                        dist[to1][to2] = cost + abs(to1 - to2);
                        pq.push({-dist[to1][to2], to1, to2});

                    }
                }
            }
        }

        int ans = INF;
        for (int i=1; i<=n; i++) {
            if (dist[i][i] != INF) {
                for (auto &to1 : adj1[i]) {
                    for (auto &to2 : adj2[i]) {
                        if (to1 == to2) ans = min(ans, min(dist[to1][to2], dist[i][i]));
                    }
                }
            }
        }

        cout << (ans == INF ? -1 : ans) << "\n";
    }

    return 0;
}