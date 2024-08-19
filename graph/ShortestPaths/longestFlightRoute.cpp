// https://cses.fi/problemset/task/1680

#include <bits/stdc++.h>
using namespace std;

int n, m;
bool pos = false;
vector<vector<int>> adj;
vector<int> dist, trace;

int dfs(int u, int par) {
    if (u == n) {
        pos = true;
        return 1;
    }
    if (dist[u] != -1) return dist[u];

    int ans = 0;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        int tmp_ans = dfs(v, u);
        if (tmp_ans == 0) continue;
        if (tmp_ans + 1 > ans) {
            ans = tmp_ans + 1;
            trace[u] = v;
        }
    }

    return dist[u] = ans;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> m;

    adj.resize(n + 1);
    dist.assign(n + 1, -1);
    trace.assign(n + 1, -1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int ans = dfs(1, 0), root = 1;

    if (pos) {
        cout << ans << '\n';
        while (root != -1) {
            cout << root << " ";
            root = trace[root];
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}