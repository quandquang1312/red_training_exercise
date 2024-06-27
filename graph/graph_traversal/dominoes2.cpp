// https://open.kattis.com/problems/dominoes2

#include <bits/stdc++.h>
using namespace std;

int n, m, l, ans;

void dfs(int u, vector<bool>& visited, vector<vector<int>>& adj) {
    if (visited[u]) return;

    visited[u] = true;
    ans++;

    for (auto &v : adj[u])
        dfs(v, visited, adj);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        cin >> n >> m >> l;

        vector<vector<int>> adj(n+1);
        vector<bool> visited(n+1, 0);

        int a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
        }

        ans = 0;
        for (int i=0; i<l; i++) {
            cin >> a;
            dfs(a, visited, adj);
        }

        cout << ans << endl;
    }

    return 0;
}