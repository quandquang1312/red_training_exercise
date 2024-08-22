// https://vjudge.net/problem/UVA-10448

#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;

int solve(int u, int sm_up, int pathTaken, const int dst, const int costRequired) {
    if (u == dst) {
        if (sm_up != costRequired) return 1e9;
        return pathTaken;
    }

    if (sm_up >= costRequired) return 1e9;

    int ans = 1e9;
    for (auto &[v, w] : adj[u]) {
        ans = min(ans, solve(v, sm_up + w, pathTaken + 1, dst, costRequired));
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

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        adj.clear();
        adj.resize(n+1); //, vector<pair<int, int>>());

        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        int q; cin >> q;
        while (q--) {
            int u, v, w;
            cin >> u >> v >> w;

            int ans = solve(u, 0, 0, v, w);
            if (ans != 1e9) {
                cout << "Yes " << ans << "\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}