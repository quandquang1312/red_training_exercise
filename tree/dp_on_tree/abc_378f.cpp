// https://atcoder.jp/contests/abc378/tasks/abc378_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    vector<bool> visited(n + 1, false);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;

        indegree[u]++;
        indegree[v]++;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int cur = 0;
    function<void(int, int)> dfs = [&] (int u, int p) -> void {
        visited[u] = true;

        for (auto &v : adj[u]) {
            if (v == p) continue;

            if (indegree[v] == 2) cur++;
            else if (indegree[v] == 3) dfs(v, u);
        }
    };

    int ans = 0;
    for (int u=1; u<=n; u++) {
        if ((indegree[u] == 3) && (visited[u] == false)) {
            cur = 0;
            dfs(u, 0);
            if (cur >= 2) ans += (cur * (cur - 1)) / 2;
        }
    }

    cout << ans << "\n";

    return 0;
}