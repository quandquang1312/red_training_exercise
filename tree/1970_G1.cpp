// https://codeforces.com/problemset/problem/1970/G1

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, c;
        cin >> n >> m >> c;

        vector<vector<int>> adj(n + 1);
        vector<int> sz(n + 1, 0);
        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        function<void(int, int)> dfs = [&] (int u, int par) -> void {
            sz[u] = 1;
            for (auto &v : adj[u]) {
                if (v == par) continue;
                dfs(v, u);
                sz[u] += sz[v];
            }
        };

        dfs(1, 0);

        int ans = INF;
        for (int i=1; i<=n; i++) {
            int remain = n - sz[i];
            if (remain) ans = min(ans, sz[i] * sz[i] + remain * remain);
        }

        cout << ans << "\n";
    }

    return 0;
}