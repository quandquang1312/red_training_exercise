// https://codeforces.com/contest/2019/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<int> depth, sub, max_depth;
vector<bool> visited;
vector<vector<int>> adj;

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;

    max_depth[u] = depth[u];
    for (auto &v : adj[u]) {
        if (visited[v]) continue;
        depth[v] = depth[u] + 1;
        dfs(v);
        sub[u] += sub[v] + 1;
        max_depth[u] = max(max_depth[u], max_depth[v]);
    }
}

void reset(int n) {
    adj.assign(n + 1, vector<int>());
    depth.assign(n + 1, 0);
    sub.assign(n + 1, 0);
    max_depth.assign(n + 1, 0);
    visited.assign(n + 1, false);
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

        reset(n);

        for (int i=1, u, v; i<n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1);

        vector<int> vect;
        for (auto &e : max_depth) vect.push_back(e);
        sort(vect.rbegin(), vect.rend());

        int removed = 0;
        map<int, vector<int>> mp;
        for (int i=1; i<=n; i++) mp[depth[i]].push_back(i);

        int ans = INF;

        // iterate in ascending order
        for (auto &node : mp) {
            // consider if a specific depth can be our answer ( current depth)

            // remove all nodes with max_depth < current depth
            // because we iterate in ascending order so we do not care about the
            // previous removed nodes
            int curr = node.first;
            while (!vect.empty() && vect.back() < curr) vect.pop_back(), removed++;

            int cost = removed;

            // remove all subtrees of the nodes with that has the depth = current depth
            for (auto &e : node.second) cost += sub[e];

            ans = min(ans, cost);
        }

        cout << ans - 1 << "\n";
    }

    return 0;
}