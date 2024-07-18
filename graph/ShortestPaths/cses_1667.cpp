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

    vector<vector<int>> adj(n+1);
    vector<int> dist(n+1, 1e9), trace(n+1, -1);
    dist[1] = 0;

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<int> q;
    q.push(1);

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        for (auto &v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                trace[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << (dist[n] == 1e9 ? "IMPOSSIBLE" : to_string(dist[n] + 1)) << endl;
    if (dist[n] != 1e9) {
        int st = n;
        vector<int> ans;
        while (st != -1) {
            ans.push_back(st);
            st = trace[st];
        }

        reverse(ans.begin(), ans.end());
        for (auto &e : ans) cout << e << " ";
        cout << endl;
    }

    return 0;
}