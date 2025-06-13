// https://codeforces.com/problemset/problem/1760/G

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n, a, b; cin >> n >> a >> b;

        vector<vector<pair<int, int>>> adj(n + 1);
        for (int i=1, u, v, w; i<n; i++) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        set<int> s;

        function<void(int, int, int)> dfs1 = [&] (int u, int p, int x) {
            if (u == b) return;
            s.insert(x);

            for (auto &[v, w] : adj[u]) {
                if (v == p) continue;
                dfs1(v, u, x ^ w);
            }
        };

        function<bool(int, int, int)> dfs2 = [&] (int u, int p, int x) {
            if (u != b && s.count(x)) return true;

            bool ans = false;
            for (auto &[v, w] : adj[u]) {
                if (v == p) continue;
                ans |= dfs2(v, u, x ^ w);
                if (ans) break;
            }

            return ans;
        };

        dfs1(a, 0, 0);
        int ans = dfs2(b, 0, 0);
        
        cout << (ans ? "YES" : "NO") << "\n";
    }

    return 0;
}