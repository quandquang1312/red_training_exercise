// https://cses.fi/problemset/task/1682

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    
    vector<vector<int>> adj(n + 1), adj_trans(n + 1);
    vector<int> dfs_num(n + 1, -1), S;

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj_trans[v].push_back(u);
    }

    function<void(int, int)> kosaraju = [&] (int u, int pass) -> void {
        dfs_num[u] = 1;
        vector<int>& neightbors = (pass == 0 ? adj[u] : adj_trans[u]);

        for (auto &v : neightbors) {
            if (dfs_num[v] == -1) 
                kosaraju(v, pass);
        }

        S.push_back(u);
    };

    for (int j=0; j<=1; j++) {
        kosaraju(1, j);
        for (int i=1; i<=n; i++) {
            if (dfs_num[i] == -1) {
                cout << "NO\n";

                if (j == 0) cout << 1 << " " << i << "\n";
                else cout << i << " " << 1 << "\n";

                return 0; 
            }
            dfs_num[i] = -1;
        }
    }

    cout << "YES\n";

    return 0;
}