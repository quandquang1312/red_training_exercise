// https://codejam.lge.com/problem/18771

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> fun(n + 1);
        for (int i=1; i<=n; i++) cin >> fun[i];

        vector<vector<int>> adj(n + 1), adj_rev(n + 1);
        vector<int> indegree(n + 1, 0);

        for (int i=1, len, x; i<=n; i++) {
            cin >> len;
            while (len--) {
                cin >> x;
                adj[x].push_back(i);
                adj_rev[i].push_back(x);
                indegree[i]++;
            }
        }

        queue<int> q;
        for (int i=1; i<=n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        // Topology Sorting
        vector<int> cost(n + 1, 0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int sm_fun = 0;
            for (auto &v : adj_rev[u]) {
                sm_fun += fun[v];
            }

            fun[u] += sm_fun;

            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }

        int ans = 0;
        for (int i=1; i<=n; i++) ans = max(ans, fun[i]);
        cout << ans << "\n";
    }

    return 0;
}