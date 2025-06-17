// https://vjudge.net/problem/UVA-872

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<vector<int>> adj(n + 1), adj_t(n + 1);
    vector<int> len(n + 1, 0), indegree(n + 1, 0), dp(n + 1, -1), nodes;

    for (int i=1, d, v; i<=n; i++) {
        nodes.push_back(i);

        cin >> len[i] >> d;
        while (d--) {
            cin >> v;
            adj[v].push_back(i);
            adj_t[i].push_back(v);
            indegree[i]++;
        }
    }

    function<void(int, int)> dfs = [&] (int u, int t) {
        if (dp[u] != -1) return;
        
        dp[u] = t;
        
        for (auto &v : adj_t[u]) {
            dfs(v, t);
        }
    };

    sort(nodes.begin(), nodes.end(), [&] (const int &a, const int &b) {
        return len[a] > len[b];
    });

    for (auto &u : nodes) dfs(u, len[u]);

    priority_queue<pair<int, int>> pq;
    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0) pq.push({dp[i], i});
    }

    int ans = -1, max_en = 0;

    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();

        ans++;
        max_en = max(max_en, ans + len[u]);

        for (auto &v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push({dp[v], v});
            }
        }
    }

    cout << max_en << "\n";

    return 0;
}