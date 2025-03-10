// https://atcoder.jp/contests/abc396/tasks/abc396_d

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = LLONG_MAX;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int ans = INF;
    vector<bool> visited(n + 1, false);
    function<void(int, int)> dfs = [&] (int u, int x) {
        if (u == n) {
            ans = min(ans, x);
            return;
        }

        visited[u] = true;

        for (auto &[v, w] : adj[u]) {
            if (visited[v] == true) continue;

            int new_xor = x ^ w; 
            dfs(v, new_xor);
        }

        visited[u] = false;
    };

    dfs(1, 0);

    cout << ans << "\n";

    return 0;
}