// https://atcoder.jp/contests/abc394/tasks/abc394_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    vector<int> visited(n + 1, false);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);

        indegree[v]++;
        indegree[u]++;
    }

    int ans = 0;
    function<int(int, int)> dfs = [&] (int u, int p) -> int {
        if (indegree[u] < 4) return 1;
        visited[u] = true;

        int cur = 1;
        priority_queue<int> pq;
        for (auto &v : adj[u]) {
            if (v == p) continue;
            pq.push(dfs(v, u));
        }

        int idx = 4, last = 0;
        while (idx--) {
            last = pq.top(); pq.pop();
            cur += last;
        }

        ans = max(ans, cur);
        if (p != 0) cur -= last;

        return cur;
    };

    for (int i=1; i<=n; i++) {
        if (!visited[i] && indegree[i] >= 4) dfs(i, 0);
    }

    cout << (ans < 5 ? -1 : ans) << "\n";

    return 0;
}