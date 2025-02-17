// https://vjudge.net/contest/692735#problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> color(n + 1, -1), color_cnt(2, 0);
    vector<int> indegree(n + 1, 0);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;

        indegree[u]++;
        indegree[v]++;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<void(int, int)> dfs = [&] (int u, int c) -> void {
        color[u] = c;
        color_cnt[c]++;
        for (auto &v : adj[u]) {
            if (color[v] == -1) {
                dfs(v, 1 - c);
            }
        }
    };

    dfs(1, 0);

    int ans = 0;
    for (int i=1; i<=n; i++) {
        int c = color[i];
        ans += (color_cnt[1 - c] - indegree[i]);
    }

    cout << ans / 2 << "\n";

    return 0;
}