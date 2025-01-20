// https://codeforces.com/gym/102694/problem/B

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

int farthest = 0, a, b;
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

void diameter() {
    int n = adj.size() - 1;

    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(1, 0, 0, adj);

    int a = farthest;

    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(a, 0, 0, adj);

    vector<int> d1 = dist;
    int b = farthest;

    dist.assign(n + 1, 0);
    dfs(b, 0, 0, adj);
    vector<int> d2 = dist;

    int d = dist[farthest];

    for (int i=1; i<=n; i++) {
        int ans_i = max(d1[i] + 1, d2[i] + 1);
        cout << max(d, ans_i) << "\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.resize(n + 1);
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    diameter();

    return 0;
}