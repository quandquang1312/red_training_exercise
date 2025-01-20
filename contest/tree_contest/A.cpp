// https://codeforces.com/gym/102694/problem/B

#include <bits/stdc++.h>
using namespace std;

int farthest = 0;
vector<int> dist;

void dfs(int u, int par, int d, vector<vector<int>> &adj) {
    dist[u] = d;
    if (dist[u] > dist[farthest]) {
        farthest = u;
    }

    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u, d + 1, adj);
    }
}

int diameter(int n, vector<vector<int>> &adj) {
    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(1, 0, 0, adj);

    int a = farthest;

    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(a, 0, 0, adj);

    return dist[farthest];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int d = diameter(n, adj);
    int circumfence = d * 3;
    cout << circumfence << "\n";

    return 0;
}