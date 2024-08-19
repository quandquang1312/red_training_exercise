// https://open.kattis.com/problems/quantumsuperposition

#include <bits/stdc++.h>
using namespace std;

int n, m;
bool pos = false;
vector<vector<int>> adj;
vector<int> dp, trace;
vector<bool> visited;

bool dfs(int u, int par, int sm, int x) {
    if (u == n) {
        if (sm == x) return true;
        return false;
    }

    if (visited[u]) return dp[u];

    int ans = 0;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        int tmp_ans = dfs(v, u, sm, x);
    }

    return dp[u] = ans;
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
    dp.assign(n + 1, false);
    visited.assign(n + 1, false);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int ans = dfs(1, 0, 0, x), root = 1;

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