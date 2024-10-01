// https://atcoder.jp/contests/abc373/tasks/abc373_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<bool> visited;
vector<int> ans;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    visited.assign(n + 1, 0);
    ans.assign(n + 1, 0);

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, -w});
    }

    queue<int> q;
    for (int i=1; i<=n; i++) {
        if (visited[i]) continue;
        visited[i] = true;

        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &[v, w] : adj[u]) {
                if (!visited[v]) {
                    ans[v] = ans[u] + w;
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    for (int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}