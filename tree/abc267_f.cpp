// https://atcoder.jp/contests/abc267/tasks/abc267_f

#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010
#define INF 1e9

int farthest, a, b;
vector<int> dist;
vector<vector<int>> adj;

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

void solve() {
    int n = adj.size() - 1;

    farthest = 0;
    dist.assign(MAXN, 0);
    dfs(1, 0, 0, adj);
    a = farthest;

    farthest = 0;
    dist.assign(MAXN, 0);
    dfs(a, 0, 0, adj);
    b = farthest;

    vector<vector<pair<int, int>>> query(n + 1);
    int q; cin >> q;
    vector<int> ans(q, -1);
    for (int i=0, u, k; i<q; i++) {
        cin >> u >> k;
        query[u].push_back({i, k});
    }

    for (int rt : {a, b}) {
        vector<int> path;
        auto dfs_2 = [&](auto&& dfs_2, int u, int p) -> void {
            for (auto &[i, k] : query[u]) {
                if (k <= path.size()) {
                    ans[i] = path[path.size() - k];
                }
            }

            path.push_back(u);
            for (auto &v : adj[u]) {
                if (v == p) continue;
                dfs_2(dfs_2, v, u);
            }
            path.pop_back();
        };

        dfs_2(dfs_2, rt, 0);
    }

    for (auto &e : ans) {
        cout << e << "\n";
    }
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    adj.resize(n + 1);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    solve();

    return 0;
}