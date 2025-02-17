// https://codeforces.com/problemset/problem/1176/E

#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tc; cin >> tc;
    while(tc--) {
        int n, m;  cin >> n >> m;
        
        vector<vector<int>> adj(n + 1);
        vector<int> color(n + 1, -1);
        vector<vector<int>> ans(2);

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        function<void(int, int)> dfs = [&] (int u, int c) -> void {
            color[u] = c;
            ans[c].push_back(u);
            for (auto &v : adj[u]) {
                if (color[v] == -1) {
                    dfs(v, 1 - c);
                }
            }
        };

        dfs(1, 0);

        if (ans[0].size() > ans[1].size()) swap(ans[0], ans[1]);

        cout << ans[0].size() << "\n";
        for (auto &u : ans[0])
            cout << u << " ";
        cout << "\n";
    }
    
    return 0;
}
