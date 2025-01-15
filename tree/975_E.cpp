// https://codeforces.com/contest/2019/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

int maxDepth = 0;
vector<int> depth, maxChildDepth, diff;

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

void update(int l, int r, int vl) {
    diff[l] += vl;
    diff[r + 1] -= vl;
}

int apply_update(int n)
{
    int mmin = 1e18;
    for (int i=1; i<=maxDepth; i++) {
        diff[i] += diff[i-1];
        mmin = min(mmin, n - diff[i]);
    }

    return mmin;
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
        diff.assign(n + 1, 0);
        maxDepth = 1;

        depth[0] = 0;

        vector<vector<int>> adj(n + 1);
        for (int i=0, u, v; i<n-1; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0, adj);

        for (int u=1; u<=n; u++) {
            update(depth[u], maxChildDepth[u], 1);
        }

        int ans = apply_update(n);

        cout << ans << "\n";
    }

    return 0;
}   