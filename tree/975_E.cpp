// https://codeforces.com/contest/2019/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

int maxDepth = 0;
vector<int> depth, maxChildDepth;

void dfs(int u, int p, vector<vector<int>>& adj) {
    depth[u] = depth[p] + 1;

    maxDepth = max(maxDepth, depth[u]);
    maxChildDepth[u] = depth[u];

    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, adj);
        maxChildDepth[u] = max(maxChildDepth[u], maxChildDepth[v]);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        depth.assign(n + 1, -1);
        maxChildDepth.assign(n + 1, -1);
        maxDepth = 1;

        depth[0] = 0;

        vector<vector<int>> adj(n + 1);
        for (int i=0, u, v; i<n-1; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0, adj);

        // for (int i=1; i<=n; i++) {
        //     cout << i << ": " << depth[i] << " - " << maxChildDepth[i] << "\n";
        // }
        /*
        d tang : number of depth[u] <= d _ tang
        d tang : number of maxChildDepth[u] >= d _ giam 
        */

        int ans = 1e18;
        for (int d=1; d<=maxDepth; d++) {
            
            int cnt = 0;
            for (int u=1; u<=n; u++) {
                if (depth[u] <= d && maxChildDepth[u] >= d) {
                    cnt++;
                }
            }

            cout << d << ": " << cnt << "\n";

            ans = min(ans, n - cnt);
        }

        cout << ans << "\n";
    }

    return 0;
}   