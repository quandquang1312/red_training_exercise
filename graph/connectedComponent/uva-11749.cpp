// https://vjudge.net/problem/UVA-11749

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<pair<int, int>>> adj;
vector<bool> visited;
int max_w;

int dfs(int u) {
    visited[u] = true;

    int ans = 1;

    for (auto &[v, w] : adj[u]) {
        if (w != max_w || visited[v]) continue;
        ans += dfs(v);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        adj.clear();
        adj.resize(n + 1);
        max_w = -9999999999999;
        visited.assign(n + 1, false);

        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            max_w = max(max_w, w);
        }

        int ans = -1;
        for (int i=1; i<=n; i++) {
            if (visited[i] == false) {
                ans = max(ans, dfs(i));
            }
        }

        cout << ans << '\n';
    }

    return 0;
}