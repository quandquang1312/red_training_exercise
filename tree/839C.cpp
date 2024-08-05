// https://codeforces.com/problemset/problem/839/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

double travel(int node, int par, vector<vector<int>>& adj) {
    if (adj[node].size() == 1 && adj[node][0] == par) {
        return 0.0;
    }

    double ans = 0;
    for (auto &v : adj[node]) {
        if (v == par) continue;

        ans += travel(v, node, adj);
    }

    if (adj[node].size() == 0) return 0.0;
    return (ans / (1.0 * (adj[node].size() - (par != 0))) + 1.0);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<vector<int>> adj(n+1);
    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    double ans = travel(1, 0, adj);
    printf("%.25lf\n", ans);

    return 0;
}