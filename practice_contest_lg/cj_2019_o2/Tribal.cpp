// https://codejam.lge.com/problem/17275

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

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        bool al[n + 1][n + 1];
        memset(al, false, sizeof al);

        vector<vector<int>> adj(n + 1);
        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int cnt = 0;
        for (int u=1; u<=n; u++) {
            int ans_u = adj[u].size() * (n - adj[u].size() - 1);
            cnt += ans_u;
        }

        cout << (cnt / 2) << endl;
    }

    return 0;
}