// https://codeforces.com/contest/2062/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<pair<int, int>> arr(n + 1);
        vector<int> A(n + 1);
        vector<vector<int>> adj(n + 1);

        for (int i=1; i<=n; i++) {
            cin >> arr[i].first >> arr[i].second;
        }

        for (int i=1, u, v; i<n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int ans = 0;

        function<void(int, int)> dfs = [&] (int u, int par) -> void {
            int mx = arr[u].first;

            for (auto &v : adj[u]) {
                if (v == par) continue;
                dfs(v, u);
                mx = max(mx, A[v]);
            }

            A[u] = min(arr[u].second, mx);

            for (auto &v : adj[u]) ans += max(0LL, A[v] - A[u]);
        };

        dfs(1, 0);

        cout << A[1] + ans << "\n";
    }

    return 0;
}