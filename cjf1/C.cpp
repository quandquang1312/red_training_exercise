// https://codejam.lge.com/contest/problem/1306/3

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, p, k;
        cin >> n >> m >> p >> k;

        vector<vector<int>> adj(n+1), adj_trans(n+1);
        vector<int> c(n+1), indegree(n+1, 0), topo, ans(n+1, 0);
        vector<bool> zeroDegree(n+1, false);
        for (int i=1; i<=n; i++) cin >> c[i];
        for (int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj_trans[v].push_back(u);
            indegree[v]++;
        }

        queue<int> q;
        for (int i=1; i<=n; i++) if (indegree[i] == 0) q.push(i), zeroDegree[i] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }

        int ttl = 0;
        for (auto &u : topo) {
            if (zeroDegree[u]) {
                ans[u] = c[u]; 
            } else {
                int max_day = -1;
                for (auto &v : adj_trans[u]) {
                    max_day = max(max_day, ans[v]);
                }

                int rm = max_day % p;
                if (rm == 0) rm = p;
                if (rm < c[u]) {
                    ans[u] = max_day + (c[u] - rm);
                } else if (rm == c[u]) {
                    ans[u] = max_day;
                } else {
                    ans[u] = max_day + (p - rm) + c[u];
                }
            }

            ttl += min(k, ans[u] - 1);
            ttl %= MOD;
        }

        for (int i=1; i<=n; i++) {
            if (indegree[i] != 0) {
                ttl += (k % MOD);
                ttl %= MOD;
            }
        }

        cout << ttl << endl;
    }

    return 0;
}